clear;
clc;

	points=read('../arg/input2.dat',-1,2);

	n=size(points,1);

	//define qtd clusters
	k=4;

	oidx=20;
	origin=points(oidx,:);

	points(oidx,:)=[];

	points=points-ones(n-1,1)*origin;

	exec functions/centers.sci;
	exec functions/all_centers.sci;
	exec functions/cost.sci;
	exec functions/full_cost.sci;
	exec functions/dist.sci;
	exec functions/kmeans3.sci;
	exec functions/plotd.sci;

	while(1)

		[cluster, pcenter] = kmeans3(points, k);

		for i=1:k
			m=size(cluster(i).entries,1);
			cluster(i).entries=cluster(i).entries+ones(m,1)*origin;
			cluster(i).entries=[cluster(i).entries; origin];
		end


		for i=1:k
			plotd(cluster,i);
		end

	end




