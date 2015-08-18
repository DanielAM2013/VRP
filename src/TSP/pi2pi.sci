// convert from 0 2pi to -2*pi to 2*pi  

function angle = pi2pi(angle)
	[n,m]=size(angle);
	for i =1:n
   		for j = 1:m
        	if angle(i,j) > %pi, angle(i,j) = angle(i,j) - 2*%pi, end
        	if angle(i,j) < -%pi, angle(i,j) = angle(i,j) + 2*%pi, end
        end
	end
endfunction

