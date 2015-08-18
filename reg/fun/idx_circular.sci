function idx = idx_circular(j,n)
	idx=1+modulo(n+j-1,n);
endfunction
