exec src/balance2.sce;

exec fun/visibP.sci;
exec fun/metrica.sci;
exec fun/metrica_last.sci;
exec fun/param.sci;
exec fun/metrica02.sci;
exec fun/NormRad.sci;
exec fun/refineP.sci;


//for i=1:k
//	B(i).n=size(B(i).idxW,2);
//	H(i).n=size(H(i).idxW,2);
//end
	W=W_opt;
	H=H_opt;
	Bold=B;


N=size(Areas_opt,1);


for k=1:N

	B(k).idxW = [1 B(k).idxW];
	B(k).n = B(k).n+1;

	if size(B(k).idxW,2)~=B(k).n
		abort
	end
	points=[W(k).coord(B(k).idxW,1:2) [1:B(k).n]'];

	[nHB, indHB,not_indHB]=myconvex_hull(points);

	indHBW=B(k).idxW(points(indHB,3));

	// HB:= indice do convexo de B
	HB(k).idxW=gsort(indHBW,'g','i');
	HB(k).n=nHB;
 
	R(k).idxW=B(k).idxW(not_indHB);
	R(k).n=size(R(k).idxW,2);

	// Inicia o caminho
	// P:= conjunto de pontos que formam o caminho
	P(k)=H(k);
	P(k).coord=W(k).coord(H(k).idxW,1:2);

	[P(k).out, P(k).in, P(k).dists, P(k).total]=param(P(k));

	exec src/tsp_while.sce;

end

for k=1:size(Areas_opt,1)
    plot([P(k).coord(:,1);P(k).coord(1,1)],[P(k).coord(:,2);P(k).coord(1,2)],'r') 
    plot([P(k).coord(:,1);P(k).coord(1,1)],[P(k).coord(:,2);P(k).coord(1,2)],'bx') 
end

