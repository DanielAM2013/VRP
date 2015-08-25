function [area]= area02(points)
	// Get the number of vertices
	n = size(points,1);

	// Initialize  area
	area = 0;

	for i = 1 : n-1
		area = area + (points(i,1)*points(i+1,2)-points(i+1,1)*points(i,2));
	end
	area=area+points(n,1)*points(1,2)-points(1,1)*points(n,2);
	area = abs(area)/2;

endfunction

