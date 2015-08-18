function saida = NormGrad(ang)

n=length(ang);
for i=1:n
//   while(ang(i)> 180)
//     ang(i) = ang(i)-360;
//   end
   while(ang(i) < 0)
     ang(i) = 360+ang(i);
   end
end
   saida=ang;
endfunction
