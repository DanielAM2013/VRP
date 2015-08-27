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
			visib = [ [next; Ai; Ao] visib];
		end
	end
endfunction
