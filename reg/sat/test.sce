v=[10 11 12 13 14 15];

n=size(v,2);

u=v(n);

p=0; q=0;
for i=2:n
	if modulo(i,2)==0
		j=n-p;
		p=p+1;
	else
		j=1+q;
		q=q+1;
	end
	disp(v(j));
end


