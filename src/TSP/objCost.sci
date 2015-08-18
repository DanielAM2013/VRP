// calculate the sum of distances
// Input: 
//	data:= set of points
//	classes:= subsets indentification
//	centers:= central points of classes of data
// Output:
//	obj:= cost
function obj = objCost (data, classes, centers)
	obj = 0;
	for i=1:max(size(data))
		sumsq = 0;
		for j = 1:min(size(data))
			//para o caso unidimensional acho que nao é para elevar ao quadrado.
			//Verificar isso...
			sumsq = sumsq + abs(data(i,j) - centers(classes(i),j));
			//sumsq = sumsq + (data(i,j) - centers(classes(i),j))^2; 
		end
		obj = obj + sumsq;
	end
endfunction
