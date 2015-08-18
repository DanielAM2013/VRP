clear;

	exec functions/centers.sci;
	exec functions/all_centers.sci;
	exec functions/cost.sci;
	exec functions/full_cost.sci;
	exec functions/dist.sci;

	points=read('../arg/input2.dat',-1,2);

	n=size(points,1);

	oidx=10;
	origin=points(oidx,:);

	points=points-ones(n,1)*origin;

	points(oidx,:)=[];
	k=4;

	args=atan(points(:,2), points(:,1));

	[trash, sorted]=gsort(args,'g','i');

	points=points(sorted,:);
	
	exec functions/kmeans3.sci;

	[cluster, pcenter]=kmeans3(points,k);

	exec functions/plotd.sci;
	exec functions/plotd_all.sci;

	plotd_all(cluster, pcenter, origin);

	exec functions/area_calc.sci;
	exec functions/heuristica2.sci;
	exec functions/full_cost.sci;

erro=1;
err=1;

while erro>1e-10 | erro<-1e-10

	//[cluster, area]=heuristica2(cluster, origin);

	k=size(cluster,1);

	area=zeros(k,1);

	for i=1:k
		Aux=[cluster(i).entries; [0, 0]];
		[trash, idx]=convex_hull(Aux');
		area(i)=area_calc(Aux(idx,:));
	end

	[trash, idx_max]=max(area);
	if idx_max > 1 & idx_max < k
		lim_inf=idx_max-1;
		lim_sup=idx_max+1;
	elseif idx_max==1
		lim_inf=k;
		lim_sup=idx_max+1;
	elseif idx_max==k
		lim_inf=idx_max-1;
		lim_sup=1;
	end

	tmp=cluster(idx_max).entries;
	m=size(tmp,1);

	area1=area_calc([ 0 0; tmp(m,:); tmp(m-1,:)]);
	area2=area_calc([ 0 0; tmp(2,:); tmp(1,:)]);

	test=dist(tmp(m,:),tmp(m-1,:)) > dist(tmp(2,:),tmp(1,:));

	if	test
		pos=m
		class=lim_sup;
	else
		pos=1
		class=lim_inf;
	end

	cluster(idx_max).entries(pos,:)=[];
	cluster(class).entries=[cluster(class).entries; tmp(pos,:)];

	nargs=1000*atan(cluster(class).entries(:,2),cluster(class).entries(:,1));

	[trash, sorted]=gsort(nargs,'g','i');

	cluster(class).entries=cluster(class).entries(sorted,:);

	clf;
	plotd_all(cluster, pcenter, origin);	

	dcost=full_cost(cluster);
	nerr=size(err,1);
	[erro, trash]=min(abs(err-ones(nerr,1)*dcost));
	err=[err; dcost];
	if nerr>15
		err=1;
	end
	x=input('test: ');
end

	clf;
	plotd_all(cluster, pcenter, origin);

	for i=1:k
		n=size(cluster(i).entries,1)
		cluster(i).entries=cluster(i).entries+ones(n,1)*origin;
	end






