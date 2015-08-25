function [Ho, Bo]=myconvex_fix_add(Wnew, Hi, Bi, idx_new)

	if idx_new == 2
		Bo=Bi
		Bo.idxW=Bo.idxW+1
		Ho.idxW=[1 Hi.idxW+1]
		Ho.n=Hi.n+1
		points=Wnew.coord(Ho.idxW,:)

		first = points(2,1:2);
		second= points(3,1:2);
		third = points(4,1:2);
		pcross = ccw(first, second, third);
		not_idxH_part=[];
                  
		while pcross < 0 & length(Ho.idxW) > 2
			posB = find(Bo.idxW > Ho.idxW(3),1);
			Bo.idxW=[Bo.idxW(1:posB-1) Ho.idxW(3) Bo.idxW(posB:Bo.n)];
			Bo.n=Bo.n+1;
			points(3,:)=[];
			Ho.idxW(3)=[];
			Ho.n=Ho.n-1;
			second=third;
			third = points(4,1:2);
			// Find next valid point on convex hull.
			pcross = ccw(first, second, third);
		end
	elseif idx_new==Wnew.n
		Bo=Bi
		Ho.idxW=[Hi.idxW Wnew.n]
		Ho.n=Hi.n+1
		points=Wnew.coord(Ho.idxW,:)

		first = points(Ho.n,1:2)
		second = points(Ho.n-1,1:2)
		third = points(Ho.n-2,1:2)
		pcross = ccw(first, second, third)
		not_idxH_part=[]
                  
		while pcross > 0 & length(Ho.idxW) > 2
			if Bo.idxW(Bo.n) > Ho.idxW(Ho.n-1)
				posB = find(Bo.idxW > Ho.idxW(Ho.n-1),1)
				Bo.idxW=[Bo.idxW(1:posB-1) Ho.idxW(Ho.n-1) Bo.idxW(posB:Bo.n)]
			else
				Bo.idxW=[Bo.idxW Ho.idxW(Ho.n-1)]
			end
			Bo.n=Bo.n+1
			points(Ho.n-1,:)=[];
			Ho.idxW(Ho.n-1)=[];
			Ho.n=Ho.n-1;
			second=third
			third = points(Ho.n-2,1:2)
			// Find next valid point on convex hull.
			pcross = ccw(first, second, third)
		end
	end

endfunction
