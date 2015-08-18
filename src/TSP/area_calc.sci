function [p_area1, p_area2]= area_calc ( x, y, dists, indi)

	// Get the number of vertices
	n = length(x);
	n_pts = length(dists)

	not_indi_idx = ones(1:n_pts)
	not_indi = [1:n_pts]

	for i=1:n
		for j=1:n_pts
			if not_indi(j)==indi(i)
				not_indi_idx(j)=0
			end
		end
	end
	not_indi=not_indi( not_indi_idx==1 );

	// Initialize  area
	p_area = 0;
	p_perimetro = 0;

	for i =1:n-1
		p_area = p_area + (x(i)*y(i+1)-x(i+1)*y(i));
		p_perimetro = p_perimetro + sqrt((x(i)-x(i+1))^2 + (y(i)-y(i+1))^2)
	end

	p_area=p_area+x(n)*y(1)-x(1)*y(n);
	p_area2 = p_area/2;

	p_perimetro = sqrt((x(n)-x(1))^2 + (y(n)-y(1))^2)

	p_area1 = p_area2 + p_perimetro+2*sum(dists(not_indi))//

endfunction
