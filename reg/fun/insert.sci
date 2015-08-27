function u=insert(x,v,i)

	n=max(size(v));

	u=v;

	if i<1 | i>n+1
		disp('indice errado');
		return;
	end

	for k=n:-1:i
		tmp=v(:,k);
		u(:,k+1)=tmp;
	end

	u(:,i)=x;

endfunction
