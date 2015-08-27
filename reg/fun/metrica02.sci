function [diffL3,diffL4,orderPdist]=metrica02(P, visib, HBC)

	// a:=HBC-Pj; b:=Pj+1-HBC;

	//  |a+b|<=|a|+|b|
	//	c:=a+b

	n=size(visib,2);

	diffL3 = zeros(1,n);
	diffL4 = zeros(1,n);
	orderPdist = zeros(4,n);

	for j=1:n
		[diffL3(j), diffL4(j), tmp]=metrica(P, visib, HBC,j);
		orderPdist(:,j)=tmp;
	end

endfunction
