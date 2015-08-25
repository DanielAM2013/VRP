function [diffL3i,diffL4i,orderPdisti]=metrica02(P, visib, HBC)

	// a:=HBC-Pj; b:=Pj+1-HBC;

	//  |a+b|<=|a|+|b|
	//	c:=a+b

	n=size(visib,2);

	diffL3i = zeros(1,n-1);
	diffL4i = zeros(1,n-1);
	orderPdisti = zeros(4,n-1);

	sel=1;

	for j=1:n-1
		a=HBC-P.coord(visib(1,j),1:2); 
		b=P.coord(visib(1,j+1),1:2)-HBC;
		c=a+b;
		pp =NormRad(P.out(visib(1,j+1))-P.in(visib(1,j+1))+P.out(visib(1,j))-P.in(visib(1,j)));
		ang_in = atan(a(2), a(1));
		ang_out =  atan(b(2),b(1));
		php=NormRad(ang_in-P.in(visib(1,j)))+NormRad(ang_out-ang_in)+NormRad(P.out(visib(1,j+1))-ang_out);

		diffL3i(j) =  norm(a)+norm(b)-norm(a+b);
		diffL4i(j) =  abs(php-pp);
		orderPdisti(:,j) = [visib(1,j); visib(1,j+1); ang_in; ang_out];
	end

endfunction
