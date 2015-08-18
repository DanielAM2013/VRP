//Esta versao balancea os angulos sempre fazendo movimentos que nao cruzem a
//desigualdade Outra diferença é que passa o angulo da area maior para a area
//menor, tranferindo de area em area.
function [Areas_out, W_out, H_out, B_out]=balance_and_fix_oo4(n_wp, k, W, H, B, Areas)

	//Encontra a classe de maior area e sua posicao na ordem das secoes no
	//sentido anti horario
	[trash, imax]=max(Areas)

	//Encontra a classe de menor area e sua posicao na ordem das secoes no
	//sentido anti horario
	[trash, imin]=min(Areas)

	propaga = imin - imax
	//Se propaga > 0, imin > imax, o movimento é no sentido anti-horario,
	//transferindo a partir do maior angulo

	//Se propaga < 0, imin < imax, o movimento é no sentido horario,
	//transferindo a partir do menor angulo


	step=sign(propaga);

	for i=0:propaga-1

		old=imax+i;
		new=old+step;

		iadd=2; irem=W(old).n; inc=0;
		if propaga < 0
			iadd=W(new).n; irem=2; inc=1;
		end

		W(new).coord=insert(W(old).coord(irem,:),W(new).coord,iadd);
		W(new).n=W(new).n+1
             
		W(old).coord(irem,:)=[]
		W(old).n=W(old).n-1

		[H(new), B(new)]=myconvex_fix_add(W(new), H(new), B(new),iadd+inc);

		[H(old), B(old)]=myconvex_hull_rem(W(old), H(old), B(old),irem);
	end

	W_out=W;
	H_out=H;
	B_out=B;

	Areas_out=Areas;
	for i=1:k
		[Area1, Area2]= area_calc(W_out(i).coord(H_out(i).idxW,1),W_out(i).coord(H_out(i).idxW,2), W_out(i).coord(:,4), H_out(i).idxW)
		Areas_out(i)=Area1;
	end


endfunction
