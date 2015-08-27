
exec src/balance2.sce;

exec fun/visibP.sci;
exec fun/metrica.sci;
exec fun/metrica_last.sci;
exec fun/param.sci;
exec fun/metrica02.sci;
exec fun/NormRad.sci;
exec fun/refineP.sci;


	W=W_opt; H=H_opt;
	Wold=W; Hold=H; Bold=B;

//refine=input('refine[0/1]? ');
//idx_fig=input('fig number:= ');

for refine=0:1

	W=Wold; H=Hold; B=Bold;

	idx_fig=1+(refine+1)/10;

	N=size(Areas_opt,1);

// Para cada rota será calculado o convexo de seu conjunto interior, em seguida
// estes pontos serão adicionados a rota, formada inicialmente pelos pontos do
// convexo original
	for k=1:N

		B(k).idxW = [1 B(k).idxW];
		B(k).n = B(k).n+1;

		if size(B(k).idxW,2)~=B(k).n
			abort
		end
		// HB:= conjunto dos pontos que pertencem ao convexo interno

		points=[W(k).coord(B(k).idxW,1:2) [1:B(k).n]'];

		[nHB, indHB,not_indHB]=myconvex_hull(points);

		indHBW=B(k).idxW(points(indHB,3));

		// HB:= indice do convexo de B
		HB(k).idxW=gsort(indHBW,'g','i');
		HB(k).n=nHB;
 
		// Inicia o caminho

		// P:= conjunto de pontos que formam a rota
		P(k)=H(k);
		P(k).coord=W(k).coord(H(k).idxW,1:2);

		[P(k).out, P(k).in, P(k).dists, P(k).total]=param(P(k));

		exec src/tsp_while.sce;

	end

	clf;
	plota_wpoo(W, H,k)
	for k=1:size(Areas_opt,1)
	    plot([P(k).coord(:,1);P(k).coord(1,1)],[P(k).coord(:,2);P(k).coord(1,2)],'r') 
    	plot([P(k).coord(:,1);P(k).coord(1,1)],[P(k).coord(:,2);P(k).coord(1,2)],'bx')
	end

	x=sprintf('fig/tsp%d_%d.png',idx_fig, modulo(10*idx_fig,10));
	xs2png(0,x);
end
