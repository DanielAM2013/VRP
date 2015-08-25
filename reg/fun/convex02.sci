function [nidxH,idxH, not_idxH]=convex02(P)

	n = size(P,1);

	if n<1
		disp('Erro conjunto vazio');
		nidxH=[];
		idxH=[];
		not_idxH=[];
		return;
	elseif n<4
		idxH=1:n;
		not_idxH=[];
		nidxH=n;
		return;
	end

	idxH=1:3;
	not_idxH=[];
	m=2;

	for i = 3:n
		// Find next valid point on convex hull.
		pcross = ccw(P(idxH(m-1),1:2), P(idxH(m),1:2), P(i,1:2))

		if pcross >= 0
			//considera que se é colinear esta na hull
			idxH = [idxH i];
			m=m+1;
		else
			not_idxH_part=[];
			while pcross < 0 & m > 2
				not_idxH_part=[idxH(m) not_idxH_part];
				idxH(m)=[];
				m=m-1;
				pcross = ccw(P(idxH(m-1),1:2), P(idxH(m),1:2), P(i,1:2));
			end
			not_idxH=[not_idxH not_idxH_part];
			idxH = [idxH i];
			m=m+1;
		end
	end

	[not_idxH,ord]=gsort(not_idxH,'g','i');

	nidxH=length(idxH)

endfunction
