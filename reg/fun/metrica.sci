function [diffL3i,diffL4i,orderPdisti]=metrica(P, visib, HBC, j)

	// a:=HBC-Pj; b:=Pj+1-HBC;

	//  |a+b|<=|a|+|b|
	//	c:=a+b

	n=size(visib,2);
	next=idx_circular(j+1,n);

	a=HBC-P.coord(visib(1,j),1:2); 
	b=P.coord(visib(1,next),1:2)-HBC;
	c=a+b;

	pp =NormRad(P.out(visib(1,next))-P.in(visib(1,next))+P.out(visib(1,j))-P.in(visib(1,j)));
	ang_in = atan(a(2), a(1));
	ang_out =  atan(b(2),b(1));
	php=NormRad(ang_in-P.in(visib(1,j)))+NormRad(ang_out-ang_in)+NormRad(P.out(visib(1,next))-ang_out);

	diffL3i =  norm(a)+norm(b)-norm(a+b);
	diffL4i =  abs(php-pp);
	orderPdisti = [visib(1,j); visib(1,next); ang_in; ang_out];

endfunction
