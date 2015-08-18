function [diffL3i, diffL4i, orderPdisti]=metrica( P, visib, HBC, j)

	dist_PP= norm( P.coord(visib(1,j+1),1:2)-P.coord(visib(1,j),1:2) )
	dist_PHP= norm(P.coord(visib(1,j+1),1:2)-HBC)+ norm(HBC-P.coord(visib(1,j),1:2))
	total_ang_PP= abs(NormRad(P.out(visib(1,j+1))-P.in(visib(1,j+1)))) + abs(NormRad(P.out(visib(1,j))-P.in(visib(1,j))))
	ang_HBC_in=  atan(HBC(2)-P.coord(visib(1,j),2), HBC(1)-P.coord(visib(1,j),1))
	ang_HBC_out=  atan(P.coord(visib(1,j+1),2)-HBC(2), P.coord(visib(1,j+1),1)-HBC(1))
	total_ang_PHP= abs(NormRad(ang_HBC_in-P.in(visib(1,j))))+abs(NormRad(ang_HBC_out-ang_HBC_in))+abs(NormRad(P.out(visib(1,j+1))-ang_HBC_out))

	diffL3i =  (dist_PHP-dist_PP)
	diffL4i =  abs(total_ang_PHP-total_ang_PP)
	orderPdisti = [visib(1,j);visib(1,j+1);ang_HBC_in;ang_HBC_out]

endfunction
