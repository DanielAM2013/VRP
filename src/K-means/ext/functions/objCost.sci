function obj = objCost (data, classes, centers)
  obj = 0;
    for i=1:max(size(data))
       sumsq = 0;
       for j = 1:min(size(data))
           sumsq = sumsq + (data(i,j) - centers(classes(i),j))^2;
       end
       obj = obj + sumsq;
    end
endfunction
