// convert from -pi pi to 0 2pi
function angle = pi22pi(angle)
[n,m]=size(angle);
for i =1:n
    for j = 1:m
        if angle(i,j) < 0, angle(i,j) = angle(i,j) + 2*%pi, end
    end
end
endfunction
