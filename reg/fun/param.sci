function [phase_out, phase_in, dists, total]=param(P)


	dists		= zeros(1,P.n);
	phase_out	= zeros(1,P.n);
	phase_in	= zeros(1,P.n);

	for i=1:P.n-1
		tmp=P.coord(i+1,1:2)-P.coord(i,1:2);
		dists(i)=norm(tmp);
		phase_out(i)=atan(tmp(2), tmp(1));
	end
	tmp=P.coord(P.n,1:2)-P.coord(1,1:2);
	dists(P.n)=norm(tmp);
	phase_out(P.n)=atan(tmp(2),tmp(1));

	phase_in(2:P.n) = phase_out(1:P.n-1);
	phase_in(1)=phase_out(P.n);
	total=sum(dists);

endfunction
