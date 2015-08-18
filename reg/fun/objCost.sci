// calculate the sum of distances
// Input: 
//	data:= set of points
//	classes:= subsets indentification
//	centers:= central points of classes of data
// Output:
//	obj:= cost
function obj = objCost (data, classes, centers)

	obj = 0;
	[n m]=size(data);
	for i=1:n
		sumsq = 0;
//		for j = 1:m
			//para o caso unidimensional acho que nao é para elevar ao quadrado.
			//Verificar isso...
//			sumsq = sumsq + abs(data(i,j) - centers(classes(i),j));
			sumsq = sumsq + norm(data(i,:) - centers(classes(i),:),2)^2; 
//		end
		obj = obj + sumsq;
	end
endfunction
