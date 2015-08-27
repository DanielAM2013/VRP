function [Pout,ajusta] = refineP(Pin,W)

	dists= zeros(1,Pin.n)
	hd_out = zeros(1,Pin.n)
	hd_in = zeros(1,Pin.n) 
	ajusta=0    

	i=1;
	if abs(NormRad(%pi-abs(Pin.out(i) - Pin.in(i)))) < %pi/4
             
             idxr=[Pin.n-1, Pin.n, i, i+1, i+2]
             
             idxv=[idxr;
                  idxr(1) idxr(3) idxr(2) idxr(4) idxr(5);
                  idxr(1) idxr(4) idxr(3) idxr(2) idxr(5);
                  idxr(1) idxr(2) idxr(4) idxr(3) idxr(5);
                  idxr(1) idxr(3) idxr(4) idxr(2) idxr(5);
                  idxr(1) idxr(4) idxr(2) idxr(3) idxr(5)];
                  
             P1=Pin.coord(idxr(1),1:2)
             P2=Pin.coord(idxr(2),1:2)
             P3=Pin.coord(idxr(3),1:2)
             P4=Pin.coord(idxr(4),1:2)
             P5=Pin.coord(idxr(5),1:2)
             d1 = norm(P1-P2)+ norm(P2-P3) + norm(P3-P4) + norm(P4-P5)
             d2 = norm(P1-P3)+ norm(P3-P2) + norm(P2-P4) + norm(P4-P5)
             d3 = norm(P1-P4)+ norm(P4-P3) + norm(P3-P2) + norm(P2-P5)
             d4 = norm(P1-P2)+ norm(P2-P4) + norm(P4-P3) + norm(P3-P5)
             d5 = norm(P1-P3)+ norm(P3-P4) + norm(P4-P2) + norm(P2-P5)
             d6 = norm(P1-P4)+ norm(P4-P2) + norm(P2-P3) + norm(P3-P5)
             [val,idx_min]=min([d1,d2,d3,d4,d5,d6])
             
             
             if idx_min > 1 then
                
                ajusta=1
                idxW=Pin.idxW
                idxW(Pin.n)=Pin.idxW(idxv(idx_min,2))
                idxW(1:2)=Pin.idxW(idxv(idx_min,3:4))
             end
         end
      
         i=2
         if abs(NormRad(%pi-abs(Pin.out(i) - Pin.in(i)))) < %pi/4
             idxr=[Pin.n, i-1, i, i+1, i+2]
             
             idxv=[idxr;
                  idxr(1) idxr(3) idxr(2) idxr(4) idxr(5);
                  idxr(1) idxr(4) idxr(3) idxr(2) idxr(5);
                  idxr(1) idxr(2) idxr(4) idxr(3) idxr(5);
                  idxr(1) idxr(3) idxr(4) idxr(2) idxr(5);
                  idxr(1) idxr(4) idxr(2) idxr(3) idxr(5)];
                  
             P1=Pin.coord(idxr(1),1:2)
             P2=Pin.coord(idxr(2),1:2)
             P3=Pin.coord(idxr(3),1:2)
             P4=Pin.coord(idxr(4),1:2)
             P5=Pin.coord(idxr(5),1:2)
             d1 = norm(P1-P2)+ norm(P2-P3) + norm(P3-P4) + norm(P4-P5)
             d2 = norm(P1-P3)+ norm(P3-P2) + norm(P2-P4) + norm(P4-P5)
             d3 = norm(P1-P4)+ norm(P4-P3) + norm(P3-P2) + norm(P2-P5)
             d4 = norm(P1-P2)+ norm(P2-P4) + norm(P4-P3) + norm(P3-P5)
             d5 = norm(P1-P3)+ norm(P3-P4) + norm(P4-P2) + norm(P2-P5)
             d6 = norm(P1-P4)+ norm(P4-P2) + norm(P2-P3) + norm(P3-P5)
             [val,idx_min]=min([d1,d2,d3,d4,d5,d6])


             if idx_min > 1 then
                ajusta=2
                idxW=Pin.idxW
                idxW(1:3)=Pin.idxW(idxv(idx_min,2:4))
             end
             
         end 

      for i=3:Pin.n-2
         if abs(NormRad(%pi-abs(Pin.out(i) - Pin.in(i)))) < %pi/4
             idxr=[i-2, i-1, i, i+1, i+2]
             
             idxv=[idxr;
                  idxr(1) idxr(3) idxr(2) idxr(4) idxr(5);
                  idxr(1) idxr(4) idxr(3) idxr(2) idxr(5);
                  idxr(1) idxr(2) idxr(4) idxr(3) idxr(5);
                  idxr(1) idxr(3) idxr(4) idxr(2) idxr(5);
                  idxr(1) idxr(4) idxr(2) idxr(3) idxr(5)];
                  
             P1=Pin.coord(idxr(1),1:2)
             P2=Pin.coord(idxr(2),1:2)
             P3=Pin.coord(idxr(3),1:2)
             P4=Pin.coord(idxr(4),1:2)
             P5=Pin.coord(idxr(5),1:2)
             d1 = norm(P1-P2)+ norm(P2-P3) + norm(P3-P4) + norm(P4-P5)
             d2 = norm(P1-P3)+ norm(P3-P2) + norm(P2-P4) + norm(P4-P5)
             d3 = norm(P1-P4)+ norm(P4-P3) + norm(P3-P2) + norm(P2-P5)
             d4 = norm(P1-P2)+ norm(P2-P4) + norm(P4-P3) + norm(P3-P5)
             d5 = norm(P1-P3)+ norm(P3-P4) + norm(P4-P2) + norm(P2-P5)
             d6 = norm(P1-P4)+ norm(P4-P2) + norm(P2-P3) + norm(P3-P5)
             [val,idx_min]=min([d1,d2,d3,d4,d5,d6])


             if idx_min > 1 then
                ajusta=3
                idxW=Pin.idxW
                idxW(i-1:i+1)=Pin.idxW(idxv(idx_min,2:4))
             end
            
         end
       end
      
         i=Pin.n-1
         if abs(NormRad(%pi-abs(Pin.out(i) - Pin.in(i)))) < %pi/4
             idxr=[i-2, i-1, i, i+1, 1]
             
             idxv=[idxr;
                  idxr(1) idxr(3) idxr(2) idxr(4) idxr(5);
                  idxr(1) idxr(4) idxr(3) idxr(2) idxr(5);
                  idxr(1) idxr(2) idxr(4) idxr(3) idxr(5);
                  idxr(1) idxr(3) idxr(4) idxr(2) idxr(5);
                  idxr(1) idxr(4) idxr(2) idxr(3) idxr(5)];
                  
             P1=Pin.coord(idxr(1),1:2)
             P2=Pin.coord(idxr(2),1:2)
             P3=Pin.coord(idxr(3),1:2)
             P4=Pin.coord(idxr(4),1:2)
             P5=Pin.coord(idxr(5),1:2)
             d1 = norm(P1-P2)+ norm(P2-P3) + norm(P3-P4) + norm(P4-P5)
             d2 = norm(P1-P3)+ norm(P3-P2) + norm(P2-P4) + norm(P4-P5)
             d3 = norm(P1-P4)+ norm(P4-P3) + norm(P3-P2) + norm(P2-P5)
             d4 = norm(P1-P2)+ norm(P2-P4) + norm(P4-P3) + norm(P3-P5)
             d5 = norm(P1-P3)+ norm(P3-P4) + norm(P4-P2) + norm(P2-P5)
             d6 = norm(P1-P4)+ norm(P4-P2) + norm(P2-P3) + norm(P3-P5)
             [val,idx_min]=min([d1,d2,d3,d4,d5,d6])

             


             if idx_min > 1 then
                ajusta=4
                idxW=Pin.idxW
                idxW(Pin.n-2:Pin.n)=Pin.idxW(idxv(idx_min,2:4))
             end

             
         end
                 
      
         i=Pin.n
         if abs(NormRad(%pi-abs(Pin.out(i) - Pin.in(i)))) < %pi/4
             idxr=[i-2, i-1, i, 1, 2]
             
             idxv=[idxr;
                  idxr(1) idxr(3) idxr(2) idxr(4) idxr(5);
                  idxr(1) idxr(4) idxr(3) idxr(2) idxr(5);
                  idxr(1) idxr(2) idxr(4) idxr(3) idxr(5);
                  idxr(1) idxr(3) idxr(4) idxr(2) idxr(5);
                  idxr(1) idxr(4) idxr(2) idxr(3) idxr(5)];
                  
             P1=Pin.coord(idxr(1),1:2)
             P2=Pin.coord(idxr(2),1:2)
             P3=Pin.coord(idxr(3),1:2)
             P4=Pin.coord(idxr(4),1:2)
             P5=Pin.coord(idxr(5),1:2)
             d1 = norm(P1-P2)+ norm(P2-P3) + norm(P3-P4) + norm(P4-P5)
             d2 = norm(P1-P3)+ norm(P3-P2) + norm(P2-P4) + norm(P4-P5)
             d3 = norm(P1-P4)+ norm(P4-P3) + norm(P3-P2) + norm(P2-P5)
             d4 = norm(P1-P2)+ norm(P2-P4) + norm(P4-P3) + norm(P3-P5)
             d5 = norm(P1-P3)+ norm(P3-P4) + norm(P4-P2) + norm(P2-P5)
             d6 = norm(P1-P4)+ norm(P4-P2) + norm(P2-P3) + norm(P3-P5)
             [val,idx_min]=min([d1,d2,d3,d4,d5,d6])

           
             if idx_min > 1 then
                ajusta=5
                idxW=Pin.idxW
                idxW(Pin.n-1:Pin.n)=Pin.idxW(idxv(idx_min,2:3))
                idxW(1)=Pin.idxW(idxv(idx_min,4))
             end

         end
             
   if ajusta > 0 then
       
      Pin.idxW=idxW
      
      start=find(Pin.idxW==1)
      
      Pin.idxW = [Pin.idxW(start:Pin.n) Pin.idxW(1:start-1)]
      
      Pin.coord = W.coord(Pin.idxW,1:2)
      
      //claro que nao precisa calcular todos os headinds de novo, mas eu ajeito isso depois...
      dists= zeros(1,Pin.n)
      hd_out = zeros(1,Pin.n)
      hd_in = zeros(1,Pin.n) 
      for i=1:Pin.n-1
         dists(i)=norm(Pin.coord(i+1,1:2)-Pin.coord(i,1:2))
         hd_out(1,i)=atan(Pin.coord(i+1,2)-Pin.coord(i,2), Pin.coord(i+1,1)-Pin.coord(i,1))
      end
      dists(Pin.n)=norm(Pin.coord(1,1:2)-Pin.coord(Pin.n,1:2))
      hd_out(Pin.n)=atan(Pin.coord(1,2)-Pin.coord(Pin.n,2), Pin.coord(1,1)-Pin.coord(Pin.n,1))
      Pin.out=hd_out
      hd_in(2:Pin.n) = hd_out(1:Pin.n-1)
      hd_in(1)=hd_out(Pin.n) //o ponto de prtida nao tem um heading de entrada
      Pin.in=hd_in
      Pin.total=sum(dists)
      Pin.dists = dists
   end
   
   Pout=Pin  
