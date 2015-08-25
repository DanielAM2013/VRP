			for i=3:HB(k).n

				HBC=W(k).coord(HB(k).idxW(i),1:2);
				HBL=W(k).coord(HB(k).idxW(i-1),1:2);
				i_adj = idx_circular(i+1,HB(k).n);
				HBR=W(k).coord(HB(k).idxW(i_adj),1:2);

				//pega como primeiro ponto visivel o ultimo ponto visivel pela
				//direita do ponto anterior

                 i_v=visib(1,size(visib,2));
                 [visib] = visibP(HBC,HBL,HBR,P(k),i_v);
                 //se i_v nao for visivel, procura um que seja
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
