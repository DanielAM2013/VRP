function plota_wpoo(W,H,k)
    
	cores = ['rx' 'r';'gx' 'g';'bx' 'b';'yx' 'y';'cx' 'c';'mx' 'm'];

	for i=1:k
		n=size(H(i).idxW,2);
		plot(W(i).coord(:,1), W(i).coord(:,2),cores(i,1));
 		if n>0 
			plot([W(i).coord(H(i).idxW(n),1);,W(i).coord(H(i).idxW,1)],[W(i).coord(H(i).idxW(n),2);,W(i).coord(H(i).idxW,2)],cores(i,2))
		end      
	end

endfunction
