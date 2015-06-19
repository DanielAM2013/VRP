clear;

	exec functions/centers.sci;
	exec functions/all_centers.sci;
	exec functions/cost.sci;
	exec functions/full_cost.sci;
	exec functions/dist.sci;

	points=read('../arg/input2.dat',-1,2);

	n=size(points,1);

	oidx=20;
	origin=points(oidx,:);

	points=points-ones(n,1)*origin;

	points(oidx,:)=[];
	k=4;

//	args=atan(points(:,2), points(:,1));

//	[trash, sorted]=gsort(args,'g','i');

//	points=points(sorted,:);
	
	exec functions/kmeans3.sci;

	[cluster, pcenter]=kmeans3(points,k);

	exec functions/plotd.sci;
	exec functions/plotd_all.sci;

	plotd_all(cluster, pcenter, origin);

	// sort cluster in counterclockwise way
	for i=1:k
		m=size(cluster(i).entries,1);
		args=zeros(m,1);
		for j=1:m
			args(j)=atan(cluster(i).entries(j,1),cluster(i).entries(j,2));
		end
		[trash, arg_sort]=gsort(args,'g','d');
		cluster(i).entries=cluster(i).entries(arg_sort,:);
	end

	exec functions/area_calc.sci;
	exec functions/heuristica2.sci;
for t=1:6

	[cluster, area]=heuristica2(cluster, origin);

	plotd_all(cluster, pcenter, origin);	

end

	clf;
	plotd_all(cluster, pcenter, origin);


