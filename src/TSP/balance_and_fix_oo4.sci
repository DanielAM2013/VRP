// Input: 
// Areas:=

function [Areas_out, W, H, B]=balance_and_fix_oo4(n_wp, k, W, H, B, Areas)
//Esta versao balancea os angulos sempre fazendo movimentos que nao cruzem a
//desigualdade Outra diferença é que passa o angulo da area maior para a area
//menor, tranferindo de area em area.

exec area_calc.sci;
exec myconvex_hull.sci;
exec myconvex_fix_add.sci;
exec myconvex_hull_rem.sci;

//Encontra a classe de maior area e sua posicao na ordem das secoes no sentido
//anti horario

	[trash, imax]=max(Areas);
//Encontra a classe de menor area e sua posicao na ordem das secoes no sentido
//anti horario

	[trash, imin]=min(Areas);

	propaga = imin - imax
//Se propaga > 0, imin > imax, o movimento é no sentido anti-horario,
//transferindo a partir do maior angulo

//Se propaga < 0, imin < imax, o movimento é no sentido horario,
//transferindo a partir do menor angulo

	if propaga > 0
		for i=0:propaga-1
			old=imax+i
			new=old+1

			// Adiciona o último ponto da classe old para new
			W(new).coord=[[0 0 0 0]; W(new).coord];
			W(new).coord(2,:)=W(old).coord(W(old).n,:);
			//W(new).coord=[W(new).coord; W(old).coord(2,:)];
			W(new).n=W(new).n+1;

			// Remove o último ponto da classe old
			W(old).coord(W(old).n,:)=[];
			W(old).n=W(old).n-1;

			[H(new), B(new)]=myconvex_fix_add(W(new), H(new), B(new),2);
             
			[H(old), B(old)]=myconvex_hull_rem(W(old), H(old), B(old), W(old).n+1);
    	end
	elseif propaga < 0
    	for i=0:-1:propaga+1
			old=imax+i;
			new=old-1;

			W(new).coord=[W(new).coord; W(old).coord(2,:)];
			W(new).n=W(new).n+1;

			W(old).coord(2,:)=[];
			W(old).n=W(old).n-1;

			[H(new), B(new)]=myconvex_fix_add(W(new), H(new), B(new), W(new).n);

			[H(old), B(old)]=myconvex_hull_rem(W(old), H(old), B(old), 2)
		end
	end

//	W_out=W;
//	H_out=H;
//	B_out=B;

	//re-calcula as areas
//	Areas_out=Areas
	for i=1:k
		[Area1, Area2]= area_calc(W(i).coord(H(i).idxW,1),W(i).coord(H(i).idxW,2), W(i).coord(:,4), H(i).idxW)
		Areas_out(i)=Area1;
	end

endfunction
