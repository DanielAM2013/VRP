function [nidxH, idxH, not_idxH]=myconvex_hull(P)
// Input:
// P:= pontos para achar o convexo
// Output:
// idxH:= índice dos pontos de P que formam a casta convexa
// not_idxH:= pontos de P que não forma a casta convexa
// nidxH:= numero de pontos de idxH

exec ccw.sci;

	n = size(P,1);
	idxH=[1, 2];
	not_idxH=[];
	m=2;
	for i = 3:n
		org=P(idxH(m-1),1:2);
		pcross = ccw(org,P(idxH(m),1:2),P(i,1:2));
		if pcross==0
 			idxH = [idxH i];
			m=m+1;
    	elseif pcross > 0
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

	nidxH=length(idxH);

endfunction