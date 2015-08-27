function	[Idx]=convex_merger(points,idxC1,idxC2)

	// c1 is outer to c2
	n=size(idxC1,2);
	n2=size(idxC2,2);
	Idx=idxC1;
	for i=1:n2
		for j=1:n
			next=1+modulo(j,n);
			a=norm(points(Idx(j),:)-points(idxC2(i),:));
			b=norm(points(idxC2(i),:)-points(Idx(next),:));
			c=norm(points(Idx(j),:)-points(Idx(next),:));
			inc(j)=a+b-c;
		end
		[trash, idx]=min(inc);
		Idx=insert(idxC2(i),Idx,idx+1);
		n=n+1;
	end

endfunction
