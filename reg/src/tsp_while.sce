//	O objetivo agora é descobrir para cada ponto de HB quais os locais
//	candidatos em que ele vai poder entrar. Isso é feito calculando a
//	visibilidade. Depois que encontrar os pontos, basta calcular o menor cauchy
//	para este ponto.

	// Enquanto houver pontos internos ( que não pertenção ao convexo ) continua      
	while B(k).n > 1 

		exec src/tsp_while_if.sce;

		[HBchange, idx_min] = min(HB(k).candist(1,:));
		idx_newW = HB(k).candist(6,idx_min);

		PidxW=[];

		// Adiciona um ponto de HB mais próximo do convexo H na rota
		idxHB=HB(k).candist(2,idx_min);
		if idxHB == P(k).n 
			PidxW=[P(k).idxW idx_newW];
			tetra=[P(k).idxW(P(k).n) idx_newW P(k).idxW(1:2)];
		else
			PidxW=[P(k).idxW(1:idxHB) idx_newW P(k).idxW(idxHB+1:P(k).n)];
		end

		P(k).coord = W(k).coord(PidxW,:);
		P(k).n=P(k).n+1;
		P(k).idxW=PidxW;
      
		[P(k).out, P(k).in, P(k).dists, P(k).total]=param(P(k));

if refine==1
		Pin=P(k);
		[Pout,ajusta]=refineP(Pin,W(k));
		[Pout,ajusta]=refineP(Pout,W(k));
		P(k)=Pout;
end 
		indexBout = find(B(k).idxW == idx_newW);
		B(k).idxW(indexBout) = [];
		B(k).n = B(k).n-1;

		//calcular a ordem da casca comvexa para 3 elementos
		if  B(k).n == 3
			HB(k) = B(k);
			[val, idx]=min(W(k).coord(B(k).idxW,2));
			first = W(k).coord(B(k).idxW(idx),1:2);
			second=W(k).coord(B(k).idxW(idx_circular(idx-1,3)),1:2);
			third=W(k).coord(B(k).idxW(idx_circular(idx+1,3)),1:2);
			turn_left =ccw(first,second,third);
			if turn_left >= 0 
				Idx=[ idx idx_circular(idx+1,3) idx_circular(idx-1,3)];
			else
				Idx=[ idx idx_circular(idx-1,3) idx_circular(idx+1,3)];
			end
			HB(k).idxW = B(k).idxW(Idx);
			indHBW = HB(k).idxW;
			// Obs: essa parte provavelmente não é necessária, uma vez que a
			// ordem de colocação dos pontos só influenciaria o calculo da área
		elseif B(k).n <= 2
			HB(k).n=B(k).n;
			HB(k)=B(k);
			indHBW = HB(k).idxW;
		else
			//Encontra a casca convexa dos pontos internos
			points=[W(k).coord(B(k).idxW,1:2) [1:B(k).n]'];

			[nHB, indHB,not_indHB]=myconvex_hull(points);

			indHBW=B(k).idxW(points(indHB',3)');
			HB(k).n=nHB;
		end

		if HB(k).n > 0
			HB(k).idxW=gsort(indHBW,'g','i');
		end

	end