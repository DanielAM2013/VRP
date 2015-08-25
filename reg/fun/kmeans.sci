function [classes, centers, sumd, D, err] = kmeans(data, k)

	// defaults for options
	erro		= 1e-3;

	//used for getting the number of samples
	nRows = size(data,1);

	// used to hold the distances from each sample to each class
	D = zeros (nRows, k);

	//used for convergence of the centroids
	err = 1;

	//initial sum of distances
	sumd = %inf;

	for i=1:k
		idx(1,i) = ceil((i+rand()-1)*floor(nRows/k));
  	end

	idx=gsort(idx,'g','i')
	centers = data (idx, :);
	// Run the algorithm
	while err > erro
    	// Compute squared distances
		for i = 1:k
			centroid = centers(i,:);
			for j=1:nRows
				// para o caso unidimensional
				D(j,i) = norm(data(j,:)-centroid,2)^2; 
			end
		end

		// Classify
		[trash, classes] = min(D,'c');

		// Calculate new centroids
		for i = 1:k
			// update the centroids
			elementos = data(classes==i, :);
			centers(i, :) = sum(elementos,:)/size(elementos,1);
		end

		// calculate the difference in the sum of distances
		err  = sumd - objCost (data, classes, centers);
		// update the current sum of distances
		sumd = objCost (data, classes, centers);
	end

endfunction
