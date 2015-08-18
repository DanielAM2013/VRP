function [cluster, pcenter] = kmeans3( points,k)
 
	//used for getting the number of samples
	n=size(points,1);

	pcenter = cell(k,1);
	for i=1:k
		pcenter(i).entries = points(round(n/k*(i-1)+1),:);
   	end

	//used for convergence of the centroids
	err = 1;

	//initial sum of distances
	sumd = %inf;

	cluster=cell(k,1);
	// Run the algorithm
	while err > 1e-6

		cluster=cell(k,1);
    	// Compute squared distances
    	for i = 1:n
			aux=zeros(k,1);
	     	for j=1:k
	         	aux(j) = dist(points(i,:),pcenter(j).entries)^2;
			end
			[trash, class]=min(aux);
			cluster(class).entries=[cluster(class).entries ; points(i,:)];
    	end

		// calculate the difference in the sum of distances
    	err  = sumd - full_cost(cluster);

    	// update the current sum of distances
		[sumd, pcenter]=full_cost(cluster);

	end

endfunction
