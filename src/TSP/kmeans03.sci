function [classes, centers, sumd, D, err] = kmeans(data, k, cost)

//exec objCost.sci;

	// defaults for options
	erro		= 1e-5;

	//used for getting the number of samples
	nRows = max(size(data));

	// used to hold the distances from each sample to each class
	D = zeros (nRows, k);

	//used for convergence of the centroids
	err = 1;

	//initial sum of distances
	sumd = %inf;

	idx = round(rand(1,k)*nRows);
  
	idx=gsort(idx,'g','i')
	centers = data (idx, :);

	// Run the algorithm
	while err > erro
    	// Compute squared distances
		for i = 1:k
			centroid = centers(i,:);
			for j=1:nRows
				diff_vector = data(j,:)-centroid;
				// para o caso unidimensional
				dist_j = abs(diff_vector); 
				// dist_j = (norm(diff_vector))^2;
           		D(j,i) = dist_j;
			end
		end

		// Classify
		[minD, classes] = min(D,'c');
		cluster = [minD,classes,idx(classes)'];

		// Calculate new centroids
		for i = 1:k
			// Get binary vector indicating membership in cluster i
			membership = (classes == i);
			// update the centroids
			elementos = data(membership, :);
			centers(i, :) = sum(elementos,1)/size(elementos,1);
		end

		// calculate the difference in the sum of distances
		err  = sumd - cost (data, classes, centers);
		// update the current sum of distances
		sumd = cost (data, classes, centers);
	end

endfunction
