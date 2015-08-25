//Encontra os pontos em P que sao visiveis a partir
//de um ponto na casca convexa interna.
//Isso reduz o conjunto de busca de candidatos a entrar no caminho.

function [visib] = visibP(HBC,HBL,HBR,P,i_v) 
          
      Pj=P(1).coord(i_v,1:2)
      Ang_out=P(1).out(i_v)
      Ang_in=P(1).in(i_v)
            
      //Primeiro tenho que calcular o subconjunto de visibilidade!!!
      //i = indice em P que é visivel a partir de Pcenter
      visib = []
      turn_right = (HBR(1)-HBC(1))*(Pj(2)-HBC(2))-(Pj(1)-HBC(1))*(HBR(2)-HBC(2))
      turn_left = (HBL(1)-HBC(1))*(Pj(2)-HBC(2))-(Pj(1)-HBC(1))*(HBL(2)-HBC(2))
      //verifica a visibilidade do ponto pivot
      if turn_right <= 0 | turn_left >= 0 then
//         visib = [i_v;norm(HBC-Pj)]
         visib = [i_v;Ang_in;Ang_out]
      end
                                                        
      //verifica a visibilidade dos pontos à esquerda do pivot (isso pode melhorar, pois so preciso olhar os pontos 1 vez)
      for j = i_v-1:-1:i_v-P(1).n+1
         next = idx_circular(j, P(1).n)
         Pj=P(1).coord(next,1:2)
         Ang_out=P(1).out(next)
         Ang_in=P(1).in(next)

         turn_right = (HBR(1)-HBC(1))*(Pj(2)-HBC(2))-(Pj(1)-HBC(1))*(HBR(2)-HBC(2))
         turn_left = (HBL(1)-HBC(1))*(Pj(2)-HBC(2))-(Pj(1)-HBC(1))*(HBL(2)-HBC(2))
         
         if turn_left >= 0 | turn_right <= 0 then
            visib = [[next;Ang_in;Ang_out] visib]
         else
            next = idx_circular(next+1,P(1).n)
            break
         end
      end
      last=idx_circular(next-1,P(1).n)

// return 
      //verifica a visibilidade dos pontos à direita do pivot (isso pode melhorar, pois so preciso olhar os pontos 1 vez)
     for j = i_v+1:i_v+P(1).n-1
     

//     for j = i_v+1:last+P(1).n
         next = idx_circular(j, P(1).n)
         Pj=P(1).coord(next,1:2)
         Ang_out=P(1).out(next)
         Ang_in=P(1).in(next)

         turn_right = (HBR(1)-HBC(1))*(Pj(2)-HBC(2))-(Pj(1)-HBC(1))*(HBR(2)-HBC(2))
         turn_left = (HBL(1)-HBC(1))*(Pj(2)-HBC(2))-(Pj(1)-HBC(1))*(HBL(2)-HBC(2))
         if turn_right <= 0 | turn_left >= 0 then
            visib = [visib [next;Ang_in;Ang_out]]
         else
            break
         end
      end
endfunction      
