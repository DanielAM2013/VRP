//Encontra os pontos em P que sao visiveis a partir
//de um ponto na casca convexa interna.
//Isso reduz o conjunto de busca de candidatos a entrar no caminho.
// Input:
//	HBC:=
//	HBL:=
//	HBR:=
//	P:=
//	i_v:=
// Output:
//	visib:=

function [visib] = visibP(HBC,HBL,HBR,P,i_v) 
          
	Pj=P.coord(i_v,1:2);
	// Ao:= ângulo de saída
	Ao=P.out(i_v);
	// Ai:= ângulo de entrada
	Ai=P.in(i_v);
            
	//Primeiro tenho que calcular o subconjunto de visibilidade!!!
	// i:= indice em P que é visivel a partir de Pcenter
	visib = [];
	turn_right = ccw(HBC,HBR,Pj);
	turn_left = ccw(HBC,HBL,Pj);

	// verifica se o ponto esta fora da casca convexa de B
	if turn_right <= 0 | turn_left >= 0 then
		visib = [i_v; Ai; Ao];
	end

	//verifica a visibilidade dos pontos à esquerda do pivot (isso pode
	//melhorar, pois so preciso olhar os pontos 1 vez)

//	for j = i_v-1:-1:i_v-P(1).n+1
//		next = idx_circular(j, P(1).n);
//		Pj=P(1).coord(next,1:2);
//		Ao=P(1).out(next);
//		Ai=P(1).in(next);

//		turn_right = ccw(HBC,HBR,Pj);
//		turn_left = ccw(HBC,HBL,Pj);
 
//		if turn_left >= 0 | turn_right <= 0 then
//			visib = [[next;Ai;Ao] visib];
//		else
//			next = idx_circular(next+1,P(1).n);
//			break;
//		end
//	end
	//verifica a visibilidade dos pontos à direita do pivot (isso pode melhorar,
	//pois so preciso olhar os pontos 1 vez)

//	for j = i_v+1:i_v+P(1).n-1
//		next = idx_circular(j, P(1).n);
//		Pj=P(1).coord(next,1:2);
//		Ao=P(1).out(next);
//		Ai=P(1).in(next);

//		turn_right=ccw(HBC,HBR,Pj);
//		turn_left=ccw(HBC,HBL,Pj);
//		if turn_right <= 0 | turn_left >= 0 then
//			visib = [visib [next; Ai; Ao]];
//		else
//			break;
//		end
//	end

	visib=[];
	for j=i_v+1:i_v+P.n-1
		next = idx_circular(j, P.n);
		Pj=P.coord(next,1:2);
		Ao=P.out(next);
		Ai=P.in(next);
		turn_right=ccw(HBC,HBR,Pj);
		turn_left=ccw(HBC,HBL,Pj);
		if turn_right <= 0 | turn_left >= 0 
			visib = [ visib [next; Ai; Ao]];
		elseif turn_right >=0 | turn_left <= 0
			visib = [ visib [next; Ai; Ao]];
		end
	end
endfunction
