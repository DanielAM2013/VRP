exec myconvex_hull.sci
exec pi2pi.sci
exec idx_circular.sci
exec visibP.sci
exec metrica.sci
exec metrica_last.sci
exec NormRad.sce
exec refineP.sce

W=W_opt
H=H_opt

for k=1:size(Areas_opt,1)
            
	//Encontra a casca convexa dos pontos internos
	//este caso inclui de novo a origem. Se isso funcionar nao precisa mais
	//reorganizar os pontos
	
	B(k).idxW = [1 B(k).idxW];
	B(k).n = B(k).n+1;
	//lembrar de retirar isso se eu nao quiser fazer assim
	points=[W(k).coord(B(k).idxW,1:2) [1:B(k).n]']
	[nHB, indHB,not_indHB]=myconvex_hull(points);
                   
	indHBW=B(k).idxW(points(indHB',3)')
    
	HB(k).idxW=gsort(indHBW,'g','i')
	HB(k).n=nHB

	R(k).idxW=B(k).idxW(not_indHB)
	R(k).n=size(R(k).idxW,2)
          
    //inicializa o caminho
      
	P(k)=H(k);
	P(k).coord=W(k).coord(P(k).idxW,1:2)
      
    P(k).n=size(P(k).idxW,2)
	//calcula os headings e o tamanho do vertices, sendo o primeiro o de entrada
	//e o segundo o de saida
	
	dists= zeros(1,P(k).n)
	hd_out = zeros(1,P(k).n)
	hd_in = zeros(1,P(k).n) 
	for i=1:P(k).n-1
    	dists(i)=norm(P(k).coord(i+1,1:2)-P(k).coord(i,1:2))
		hd_out(1,i)=atan(P(k).coord(i+1,2)-P(k).coord(i,2), P(k).coord(i+1,1)-P(k).coord(i,1))
	end
      dists(P(k).n)=norm(P(k).coord(1,1:2)-P(k).coord(P(k).n,1:2))
      hd_out(P(k).n)=atan(P(k).coord(1,2)-P(k).coord(P(k).n,2), P(k).coord(1,1)-P(k).coord(P(k).n,1))
      P(k).out=hd_out
      hd_in(2:P(k).n) = hd_out(1:P(k).n-1)
      hd_in(1)=hd_out(P(k).n) //o ponto de prtida nao tem um heading de entrada
      P(k).in=hd_in
      P(k).total=sum(dists)
      P(k).dists = dists
      
	//o objetivo agora é descobrir para cada ponto de HB quais os locais candidatos em que ele vai poder
    //entrar. Isso é feito calculando a visibilidade. Depois que encontrar os pontos, basta calcular o
	//menor cauchy para este ponto.
      
	//por causa de B ter sempre a origem, senao seria > 0
    while B(k).n > 1
		// Levanta o conjunto de pontos visiveis
		if HB(k).n >= 3 then  //so faz se tiver dois pontos alem da propria origem
			//Pega a primeira triade a partir do segundo ponto de HB, pois o 1o é a origem
			i=2
 			HBC=W(k).coord(HB(k).idxW(i),1:2)
 			HBL=W(k).coord(HB(k).idxW(i-1),1:2)
 			HBR=W(k).coord(HB(k).idxW(i+1),1:2)

			//pega um primeiro ponto de P que seja visivel. este indice
			//i_v vai ser usado como pivot. A partir dele para a direita
			//é visivel os pontos que fizerem curva para a direita
			i_v=1
			 
			[visib] = visibP(HBC,HBL,HBR,P(k),i_v)
  
			diffL3 = zeros(1,size(visib,2)-1)
 			diffL4 = zeros(1,size(visib,2)-1)
 			orderPdist = zeros(4,size(visib,2)-1)
                          
 			for j=1:size(visib,2)-1
				//calcula a metrica, que no caso é a diferenca de cauchy + a
				//diferenca entre as mudancas de headings

 				[diffL3i, diffL4i,orderPdisti] = metrica(P(k), visib, HBC, j)
 				diffL3(j) =  diffL3i
				diffL4(j) =  diffL4i
				orderPdist(:,j) = orderPdisti
 			end
 			diffL=diffL3+diffL4;
 			[val, idx]=min(diffL)
 			minorderPPdist = orderPdist(:,idx)
 			if idx > 0,HB(k).candidateDist = [val;minorderPPdist;HB(k).idxW(i)],end

			for i=3:HB(k).n //se nao considerar a origem em B comeca de i=2
				//Pega as outras triades no sentido anti horario (direita)
				HBC=W(k).coord(HB(k).idxW(i),1:2) //trata-se do caso em que HBC ultimo ponto
  				HBL=W(k).coord(HB(k).idxW(i-1),1:2)
  				//ajusta o indice maior para o ultimo caso
     			i_adj = idx_circular(i+1,HB(k).n)
 				HBR=W(k).coord(HB(k).idxW(i_adj),1:2)
      
				//pega como primeiro ponto visivel o ultimo ponto visivel pela direita do ponto anterior
                 i_v=visib(1,size(visib,2))
                 [visib] = visibP(HBC,HBL,HBR,P(k),i_v)      
                 //se i_v nao for visivel, procura um que seja
                 while size(visib) == 0
                     i_v=idx_circular(i_v+1,P(k).n)
                    [visib] = visibP(HBC,HBL,HBR,P(k),i_v) 
                 end
            
                 diffL3 = zeros(1,size(visib,2)-1)
                 diffL4 = zeros(1,size(visib,2)-1)
                 orderPdist = zeros(4,size(visib,2)-1)
                 for j=1:size(visib,2)-1
                      [diffL3i, diffL4i,orderPdisti] = metrica(P(k), visib, HBC, j)
                       diffL3(j) = diffL3i
                       diffL4(j) = diffL4i
                       orderPdist(:,j) = orderPdisti
                 end
                 diffL=diffL3+diffL4

                [val, idx]=min(diffL)
                 minorderPPdist = orderPdist(:,idx)
                if idx > 0,HB(k).candidateDist = [HB(k).candidateDist [val;minorderPPdist;HB(k).idxW(i)]],end
           end
        else  //esta terminando  HB, so tem um ponto + a origem, nao precisa calcular visib, pois todos sao visiveis
           HB(k).candidateDist = []
           i=2
           visib = 1:P(k).n
           HBC=W(k).coord(HB(k).idxW(i),1:2)

           diffL3 = zeros(1,size(visib,2))
           diffL4 = zeros(1,size(visib,2))
           orderPdist = zeros(4,size(visib,2))

           for j=1:P(k).n-1
                  [diffL3i, diffL4i,orderPdisti] = metrica(P(k), visib, HBC, j)
                  diffL3(j) =  diffL3i
                  diffL4(j) =  diffL4i
                  orderPdist(:,j) = orderPdisti
           end
           [diffL3i, diffL4i,orderPdisti] = metrica_last(P(k), visib, HBC, j)
           diffL3(P(k).n) = diffL3i
           diffL4(P(k).n) =  diffL4i
           orderPdist(:,P(k).n) = orderPdisti     

           diffL=diffL3+diffL4
           [val, idx]=min(diffL)
           minorderPPdist = orderPdist(:,idx)
           HB(k).candidateDist = [HB(k).candidateDist [val;minorderPPdist;HB(k).idxW(i)]]
    end     

    [HBchange, idx_min] = min(HB(k).candidateDist(1,:))
    idx_newW = HB(k).candidateDist(6,idx_min)
       
    PidxW=[]       

    if HB(k).candidateDist(2,idx_min) == P(k).n  //significa que a transicao é do ultimo para o primeiro
       PidxW=[P(k).idxW idx_newW]
       tetra=[P(k).idxW(P(k).n) idx_newW P(k).idxW(1:2)]
    else
       PidxW=[P(k).idxW(1:HB(k).candidateDist(2,idx_min)) idx_newW P(k).idxW(HB(k).candidateDist(2,idx_min)+1:P(k).n)]
    end



      P(k).coord = W(k).coord(PidxW,:);
      P(k).n=P(k).n+1;
      P(k).idxW=PidxW;
      
      //claro que nao precisa calcular todos os headinds de novo, mas eu ajeito isso depois...
      dists= zeros(1,P(k).n)
      hd_out = zeros(1,P(k).n)
      hd_in = zeros(1,P(k).n) 
      for i=1:P(k).n-1
         dists(i)=norm(P(k).coord(i+1,1:2)-P(k).coord(i,1:2))
         hd_out(1,i)=atan(P(k).coord(i+1,2)-P(k).coord(i,2), P(k).coord(i+1,1)-P(k).coord(i,1))
      end
      dists(P(k).n)=norm(P(k).coord(1,1:2)-P(k).coord(P(k).n,1:2))
      hd_out(P(k).n)=atan(P(k).coord(1,2)-P(k).coord(P(k).n,2), P(k).coord(1,1)-P(k).coord(P(k).n,1))

      P(k).out=hd_out
      hd_in(2:P(k).n) = hd_out(1:P(k).n-1)
      hd_in(1)=hd_out(P(k).n) //o ponto de prtida nao tem um heading de entrada
      P(k).in=hd_in
      P(k).total=sum(dists)
      P(k).dists = dists
      
      Pin=P(k)
      [Pout,ajusta]=refineP(Pin,W(k))
      [Pout,ajusta]=refineP(Pout,W(k))
      P(k)=Pout
 
      indexBout = find(B(k).idxW == idx_newW)
      B(k).idxW(indexBout) = [];     
      B(k).n = B(k).n-1

      //calcular a ordem da casca comvexa para 3 elementos
      if  B(k).n == 3
          HB(k) = B(k);
          [val, idx]=min(W(k).coord(B(k).idxW,2))
          first = W(k).coord(B(k).idxW(idx),1:2)
          second=W(k).coord(B(k).idxW(idx_circular(idx-1,3)),1:2)
          third=W(k).coord(B(k).idxW(idx_circular(idx+1,3)),1:2)
          turn_left = (third(1)-first(1))*(second(2)-first(2))-(second(1)-first(1))*(third(2)-first(2))
          if turn_left >= 0 // nao estou tratando o caso de serem colineares!!!
             HB(k).idxW = [B(k).idxW(idx) B(k).idxW(idx_circular(idx+1,3)) B(k).idxW(idx_circular(idx-1,3))]
          else
             HB(k).idxW = [B(k).idxW(idx) B(k).idxW(idx_circular(idx-1,3)) B(k).idxW(idx_circular(idx+1,3))]
          end
          indHBW = HB(k).idxW;
           R(k).idxW=[];
           R(k).n=0;
      elseif B(k).n <= 2 // para os casos em que B e HB são os mesmos
          HB(k).n=B(k).n
          HB(k)=B(k);
          indHBW = HB(k).idxW;
           R(k).idxW=[];
           R(k).n=0;
      else
      //Encontra a casca convexa dos pontos internos
        points=[W(k).coord(B(k).idxW,1:2) [1:B(k).n]']

        [nHB, indHB,not_indHB]=myconvex_hull(points);
            
        indHBW=B(k).idxW(points(indHB',3)')
        HB(k).n=nHB
        R(k).idxW=B(k).idxW(points(not_indHB',3))
        R(k).n=size(R(k).idxW,2)
      end

      if HB(k).n > 0
      
          HB(k).idxW=gsort(indHBW,'g','i')

//          plot(W(k).coord(HB(k).idxW,1),W(k).coord(HB(k).idxW,2),'r')               

//          if R(k).n > 0
//              plot(W(k).coord(R(k).idxW,1),W(k).coord(R(k).idxW,2),'go')               
          end
      end
    end


end

for k=1:size(Areas_opt,1)
    plot([P(k).coord(:,1);P(k).coord(1,1)],[P(k).coord(:,2);P(k).coord(1,2)],'r') 
    plot([P(k).coord(:,1);P(k).coord(1,1)],[P(k).coord(:,2);P(k).coord(1,2)],'bx') 
end

