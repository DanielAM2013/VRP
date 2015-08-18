// convert from 0 2pi to -2*pi to 2*pi  

function idx = idx_circular(j,n)
   idx = 1+(((j-1)-fix((j-1)/n)*n)+n)-fix((((j-1)-fix((j-1)/n)*n)+n)/n)*n;
endfunction
