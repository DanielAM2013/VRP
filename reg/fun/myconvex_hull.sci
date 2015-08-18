function [nidxH,idxH, not_idxH]=myconvex_hull(P)

	n = size(P,1);

	// m will denote the number of P on the convex hull.
	idxH=[1, 2];
	not_idxH=[];
	m=2;

	for i = 3:n
		// Find next valid point on convex hull.
		pcross = ccw(P(idxH(m-1),1:2), P(idxH(m),1:2), P(i,1:2))
		if pcross == 0
			idxH = [idxH i]//considera que se é colinear esta na hull
			m=m+1 
		elseif pcross > 0
			idxH = [idxH i]
			m=m+1 
		else
			not_idxH_part=[]
			while pcross < 0 & m > 2
				not_idxH_part=[idxH(m) not_idxH_part]
				idxH(m)=[]
				m=m-1
				pcross = ccw(P(idxH(m-1),1:2), P(idxH(m),1:2), P(i,1:2))        
			end
			not_idxH=[not_idxH not_idxH_part]
			idxH = [idxH i]
			m=m+1
		end
	end

	[not_idxH,ord]=gsort(not_idxH,'g','i');

	nidxH=length(idxH)

endfunction
