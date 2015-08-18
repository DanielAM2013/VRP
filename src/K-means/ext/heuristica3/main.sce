clear;
clc;

	points=read('../arg/input2.dat',-1,2);

	exec functions/dist.sci;
	exec functions/centers.sci;
	exec functions/cost.sci;
	exec functions/full_cost.sci;
	exec functions/kmeans3.sci;
	exec functions/plotd.sci;
	exec functions/plotd_all.sci;
	exec functions/area_calc.sci;
	k=4;

	oidx=10;
	origin=points(oidx,:);

	n=size(points,1);

	points=points-ones(n,1)*origin;
	points(oidx,:)=[];


	args=atan(points(:,2), points(:,1));


	[trash, sorted]=gsort(args,'g','i');

	points=points(sorted,:)

	[cluster, pcenter]=kmeans3(points,k);
dcost=1;
err=1;
erro=1;
while erro>1e-7 | erro<-1e-7

	for i=1:k
		tmp=[cluster(i).entries; [0, 0]];
		[trash, idx]=convex_hull(tmp');
		area(i)=area_calc(tmp(idx,:));
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

	tmp_prev=cluster(lim_inf).entries;
	tmp=cluster(idx_max).entries;
	tmp_next=cluster(lim_sup).entries;

	m_prev=size(tmp_prev,1);
	m=size(tmp,1);
	m_next=size(tmp_next,1);

	test=dist(tmp_prev(m_prev,:),tmp(1,:)) > dist(tmp_next(1,:),tmp(m,:));

	if test
		pos=1;
		cluster(lim_inf).entries=[cluster(lim_inf).entries; tmp(pos,:)];
	else
		pos=m;
		cluster(lim_sup).entries=[tmp(pos,:); cluster(lim_sup).entries];
	end

	cluster(idx_max).entries(pos,:)=[];

	plotd_all(cluster, pcenter, origin);

	nerr=size(err,1);
	dcost=full_cost(cluster);
	[erro, trash]=min(abs(err-ones(nerr,1)*dcost));
	err =[err; dcost];
	if nerr>2
		err=1;
	end
end

	clf;
	plotd_all(cluster,pcenter,origin);


