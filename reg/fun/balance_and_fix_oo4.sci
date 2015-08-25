//Esta versao balancea os angulos sempre fazendo movimentos que nao cruzem a
//desigualdade Outra diferença é que passa o angulo da area maior para a area
//menor, tranferindo de area em area.
function [Areas_out, Wo, Ho, Bo]=balance_and_fix_oo4(n_wp, k, W, H, B, Areas)

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

	Wo=W;
	Ho=H;
	Bo=B;

	step=sign(propaga);

	for i=0:propaga-1

		old=imax+i;
		new=old+step;

		iadd=2; irem=W(old).n; inc=0;
		if propaga < 0
			iadd=W(new).n; irem=2; inc=1;
		end

		Wo(new).coord=insert(W(old).coord(irem,:),W(new).coord,iadd);
		Wo(new).n=W(new).n+1
 
		Wo(old).coord(irem,:)=[];
		Wo(old).n=W(old).n-1;

		[Ho(new), Bo(new)]=myconvex_fix_add(Wo(new), Ho(new), Bo(new),iadd+inc);

		[Ho(old), Bo(old)]=myconvex_hull_rem(Wo(old), Ho(old), Bo(old),irem);
	end

	Areas_out=Areas;
	for i=1:k
		[Area1, Area2]= area_calc(Wo(i).coord(Ho(i).idxW,1),Wo(i).coord(Ho(i).idxW,2), Wo(i).coord(:,4), Ho(i).idxW)
		Areas_out(i)=Area1;
	end

endfunction
