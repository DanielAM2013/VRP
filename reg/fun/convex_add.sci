function [Ho, Bo]=convex_add(W, Hi, Bi, point)

	Bo=Bi
	Ho=Hi;

	first = W.coord(Ho.idxW(1),1:2);
	second= W.coord(Ho.idxW(2),1:2);
	pcross = ccw(first, second, point);
    return

	while pcross < 0 & length(Ho.idxW) > 2
		// Insert Ho.idxW(idx) to Bo.idxW
		posB = find(Bo.idxW > Ho.idxW(2),1);
		Bo.idxW=[Bo.idxW(1:posB-1) Ho.idxW(2) Bo.idxW(posB:Bo.n)];
		Bo.n=Bo.n+1;

		// Remove Ho.idxW(idx)
		Ho.idxW(2)=[];
		Ho.n=Ho.n-1;

		first=second;
		second = points(Ho.idxW(2),1:2);
		pcross = ccw(first, second, point);
	end

endfunction
