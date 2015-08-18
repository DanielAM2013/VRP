function v=insert(x,v,i)

	n=max(size(v));

	if i<1 | i>n+1
		disp('indice errado');
		v=v;
		return;
	end

	for k=n:-1:i
		tmp=v(k,:);
		v(k+1,:)=tmp;
	end

	v(i,:)=x;

endfunction
