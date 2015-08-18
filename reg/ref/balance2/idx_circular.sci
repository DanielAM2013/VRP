function idx = idx_circular(j,n)
   idx = 1+(((j-1)-fix((j-1)/n)*n)+n)-fix((((j-1)-fix((j-1)/n)*n)+n)/n)*n
endfunction
