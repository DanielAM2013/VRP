function saida = NormRad(ang)

n=length(ang);
for i=1:n
   while(ang(i)> %pi)
     ang(i) = ang(i)-2*%pi;
   end
   while(ang(i) < -%pi)
     ang(i) = ang(i)+2*%pi;
   end
end
   saida=ang;
endfunction
