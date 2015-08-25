//IMPORTANTE: só funciona se H e B estiverem já consistentes, ou seja: Para o
//caso de novo ponto, este novo ponto já deve estar ordenado e os pontos tanto
//de H quanto de B que tiverem angulos maiores que ele devem ter seus indices
//incrementados.
//Semelhantemente, para o caso de remocao de pontos, todos os pontos de H e B
//com angulos maiores devem ter seus indices decrementados.
//Tem uma outra funcao que faz isso, mas não é aqui.

//idxh é a posicao de H em que houve a quebra da casca convexa. Para o caso
//de adição B aumenta e eventualmente H diminui
//Para o caso de remocao H aumenta ou fica como está, Se H aumenta, Bi diminui,
//é claro.
function [Ho, Bo]=myconvex_hull_fix(Wi,Hi,Bi,idxh)

	IdxC=idx_circular;
	//calcula o numero de pontos em B que serao testados
	tmp=Hi.idxW(IdxC(idxh+1,Hi.n))-Hi.idxW(IdxC(idxh,Hi.n));
	n=IdxC(tmp,Wi.n)-1

	//faz um teste basico, se depois que retira o ponto e reordena os pontos de
	//H continuam consecutivos, entao nao precisa fazer nada, pois nao existem
	//pontos em B que possam entrar.

	if n > 0 then
 		// estes sao os indices de B que poderam entrar em H
		idxB=[(Hi.idxW(idxh)+1):Hi.idxW(idxh)+n];
		idxPoints=[	Hi.idxW(IdxC(idxh-1,Hi.n))';
					Hi.idxW(idxh)';
					idxB';
					Hi.idxW(IdxC(idxh+1,Hi.n))'
					]';
	else
		Ho=Hi; Bo=Bi;
		return;
	end

	// P são todos os pontos em ordem de angulo
	P=Wi.coord(idxPoints,:);

	// m will denote the number of P on the convex hull.
	idxH=[1, 2];
	not_idxH=[];

	m=2
	for i = 3:n+3
		// Find next valid point on convex hull.
		pcross = ccw(P(idxH(m-1),1:2), P(idxH(m),1:2), P(i,1:2));
		if pcross >= 0
			//considera que se é colinear esta na hull
			idxH = [idxH i];
			m=m+1;
		else
			while pcross < 0 & m > 2
				idxH(m)=[];
				m=m-1;
				pcross = ccw(P(idxH(m-1),1:2), P(idxH(m),1:2),P(i,1:2));
			end
			idxH = [idxH i];
			m=m+1;
		end
	end
	nidxH=length(idxH);
	newH=idxPoints(idxH(3:nidxH-1));

	Ho.idxW=[Hi.idxW(1:idxh) newH Hi.idxW(idxh+1:Hi.n)];
	Ho.n=Hi.n+nidxH-3;

	for i=1:nidxH-3
		Bi.idxW(Bi.idxW==newH(i))=[];
	end
	Bo.n=Bi.n-(nidxH-3);

endfunction
