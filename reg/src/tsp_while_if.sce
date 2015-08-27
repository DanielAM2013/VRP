
		//por causa de B ter sempre a origem, senao seria > 0 Levanta o conjunto
		//de pontos visiveis so faz se tiver dois pontos alem da propria origem
		if HB(k).n >= 3
			//Pega a primeira triade a partir do segundo ponto de HB, pois o 1o
			//é a origem
			i=2;
			HBL=W(k).coord(HB(k).idxW(i-1),1:2);
			HBC=W(k).coord(HB(k).idxW(i),1:2);
			HBR=W(k).coord(HB(k).idxW(i+1),1:2);

            //pega um primeiro ponto de P que seja visivel. este indice
            //i_v vai ser usado como pivot. A partir dele para a direita
            //é visivel os pontos que fizerem curva para a direita
			i_v=1;
			[visib] = visibP(HBC,HBL,HBR,P(k),i_v);

			[diffL3, diffL4, orderPdist]=metrica02(P(k), visib, HBC);
			diffL=diffL3+diffL4;

			// val:= menor soma de distância e ângulo de pontos adjacêntes
			[val, idx]=min(diffL);
			minP = orderPdist(:,idx);
			HB(k).candist = [val; minP; HB(k).idxW(i)];

			for i=3:HB(k).n

				HBC=W(k).coord(HB(k).idxW(i),1:2);
				HBL=W(k).coord(HB(k).idxW(i-1),1:2);
				i_adj = idx_circular(i+1,HB(k).n);
				HBR=W(k).coord(HB(k).idxW(i_adj),1:2);

                 i_v=visib(1,size(visib,2));
                 [visib] = visibP(HBC,HBL,HBR,P(k),i_v);
                 while size(visib,2) == 0
                     i_v=idx_circular(i_v+1,P(k).n);
                    [visib] = visibP(HBC,HBL,HBR,P(k),i_v);
                 end
 
				[diffL3, diffL4, orderPdist]=metrica02(P(k), visib, HBC);
				diffL=diffL3+diffL4;

				[val, idx]=min(diffL);
				minP = orderPdist(:,idx);
				if idx > 0
					HB(k).candist = [HB(k).candist [val; minP; HB(k).idxW(i)]];
				end
			end
        else
			//esta terminando  HB, so tem um ponto + a origem, nao precisa
			//calcular visib, pois todos sao visiveis
			HB(k).candist = [];
			i=2;
			visib = 1:P(k).n;
			HBC=W(k).coord(HB(k).idxW(i),1:2);

			[diffL3, diffL4, orderPdist]=metrica02(P(k), visib, HBC);

			diffL=diffL3+diffL4;

			[val, idx]=min(diffL);
			minP = orderPdist(:,idx);
			HB(k).candist = [HB(k).candist [val;minP;HB(k).idxW(i)]];
		end  
