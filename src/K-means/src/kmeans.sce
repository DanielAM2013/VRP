//Primeiro quadrante
//C1 = rand(100, 1);
//C2 = rand(100, 1);
//Segundo quadrante
//C3 = -1*rand(100, 1);
//C4 = rand(100, 1);
//Terceiro quadrante
//C5 = -1*rand(100, 1);
//C6 = -1*rand(100, 1);
//Quarto quadrante
//C7 = rand(100, 1);
//C8 = -1*rand(100, 1);
//wp = [C1 C2;C3 C4;C5 C6;C7 C8];

wp=read('../arg/inpput.dat',400,2);


//calcula o angulo rho
wp_rho = atan(wp(:,2), wp(:,1));

//define qtd clusters
k=5;

//chama a função
//[classes, centers, sumd, D, err] = kmeans(wp_rho, k);
//function [classes, centers, sumd, D, err] = kmeans(data, k)
//------------------------------------------------------------------------------
  // defaults for options
  emptyaction = "error";
  start       = "sample";
  
  //used for getting the number of samples
  nRows = max(size(wp_rho));

  // used to hold the distances from each sample to each class
  D = zeros (nRows, k);

  //used for convergence of the centroids
  err = 1;

  //initial sum of distances
  sumd = %inf;
  // initial centroid points
  idx=[]205 72 76 360 235.];
  
  centers = wp_rho (idx,:)

  // Run the algorithm
 while err > .000001
    // Compute squared distances
    for i = 1:k
       centroid = centers(i,:);
       for j=1:nRows
           diff_vector = wp_rho(j,:)-centroid;
           dist_j = (norm(diff_vector))^2;
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
      members = wp_rho(membership, :);
      centers(i, :) = sum(members,1)/size(members,1);
    end

    // calculate the difference in the sum of distances
    err  = sumd - objCost (wp_rho, classes, centers);
    // update the current sum of distances
    sumd = objCost (wp_rho, classes, centers);
  end
 //-----------------------------------------------------------------------------
 
 
 

      membership = (classes == 1);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xr')      
    
      membership = (classes == 2);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xg')  

      membership = (classes == 3);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xb')      
    
      membership = (classes == 4);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xy')
            
      membership = (classes == 5);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xc')  
