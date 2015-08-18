function [classes, centers, sumd, D, err] = kmeans(data, k)
 
	//used for getting the number of samples
	n=size(data,1);

	// used to hold the distances from each sample to each class
	dist = zeros (n, k);

	//used for convergence of the centroids
	err = 1;

	//initial sum of distances
	sumd = %inf;

	idx=zeros(k,1);
	for i=1:k
		idx = round(n/k*(i-1)+rand(1,k)*(n/k));
   	end

	centers = data (idx, :)
	exec objCost.sci;


	// Run the algorithm
	while err > 1e-10

    	// Compute squared distances
    	for i = 1:k
       		centroid = centers(i,:);
       		for j=1:n
           		diff_vector = data(j,:)-centroid;
           		dist_j = (norm(diff_vector))^2;
           		D(j,i) = dist_j;
       		end
    	end

    	// Classify
    	[trash, classes] = min(D,'c');

     	cluster=[classes,points];
     
		sized=zeros(k,1);

		// Calculate new centroids
		for i = 1:n
			sized(classes(i))=sized(classes(i))+1;
      		centers(classes(i), :) = centers(classes(i),:)+data(i,:);
    	end
		centers=centers./size;

		// calculate the difference in the sum of distances
    	err  = sumd - objCost (data, classes, centers);

    	// update the current sum of distances
    	sumd = objCost (data, classes, centers);
	end

endfunction
