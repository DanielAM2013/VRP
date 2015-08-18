function [classes, centers, sumd, D, err] = kmeans(data, k)

  // defaults for options
  emptyaction = "error";
  start       = "sample";
  
  //used for getting the number of samples
  nRows = max(size(data));

  // used to hold the distances from each sample to each class
  D = zeros (nRows, k);

  //used for convergence of the centroids
  err = 1;

  //initial sum of distances
  sumd = %inf;

//  while 1 
      idx = round(rand(1,k)*nRows);
//      if idx(1) ~= idx(2) then
//          break
//      end
//  end
  
  idx=gsort(idx,'g','i')
  centers = data (idx, :);

  // Run the algorithm
 while err > .000001
    // Compute squared distances
    for i = 1:k
       centroid = centers(i,:);
       for j=1:nRows
           diff_vector = data(j,:)-centroid;
           dist_j = abs(diff_vector); //para o caso unidimensional
           //dist_j = (norm(diff_vector))^2;
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
    err  = sumd - objCost (data, classes, centers);
    // update the current sum of distances
    sumd = objCost (data, classes, centers);
  end
endfunction

// calculate the sum of distances
function obj = objCost (data, classes, centers)
  obj = 0;
    for i=1:max(size(data))
       sumsq = 0;
       for j = 1:min(size(data))
           sumsq = sumsq + abs(data(i,j) - centers(classes(i),j)); //para o caso unidimensional acho que nao é para elevar ao quadrado. Verificar isso...
//           sumsq = sumsq + (data(i,j) - centers(classes(i),j))^2; 
       end
       obj = obj + sumsq;
    end
endfunction
