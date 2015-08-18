// calc area counterclockwise
function p_area = area_calc(v)

	// Get the number of vertices
	n = size(v,1);

	// Calc area
	p_area = 0;
	for i =1:n-1
    	p_area = p_area + (v(i,1)*v(i+1,2)-v(i+1,1)*v(i,2));
	end
    p_area = p_area + (v(n,1)*v(1,2)-v(1,1)*v(n,2));
	p_area=abs(p_area)/2;

endfunction

