function espacos = calc_gaps(extremos_ord)
          //calcula os espacos entre as secoes
      
	n=length(extremos_ord(:,1));
	extremos_ord_cicle = [extremos_ord;extremos_ord(1,:)]
	espacos=[];
	for i=1:n
   		espacoi=extremos_ord_cicle(i+1,1)-extremos_ord_cicle(i,2);
   		if espacoi < 0,espacoi = 360 + espacoi;end
   		espacos = [espacos espacoi];
	end
endfunction      

