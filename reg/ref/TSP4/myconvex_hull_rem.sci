//function [idxH,not_idxH]=myconvex_hull(Pt)
exec idx_circular.sci

function [H_out, B_out]=myconvex_hull_rem(W_in,H_in,B_in,idx_remW)
//esta pate faz o ajuste dos indices, pois isso nao é feito na funcao hull_fix, para o caso
//de remocao de um ponto na casca convexa. Ela considera que o ponto idx_remW já foi retirado do
//conjunto W e portanto não existe mais em W_in

indice_h=find(H_in.idxW==idx_remW)
H_in.idxW(indice_h)=[]
H_in.n=H_in.n-1
H_in.idxW=[H_in.idxW(1:indice_h-1) H_in.idxW(indice_h:H_in.n)-ones(indice_h:H_in.n)]

indice_b=find(B_in.idxW>idx_remW,1)
if indice_b<>[]
B_in.idxW=[B_in.idxW(1:indice_b-1) B_in.idxW(indice_b:B_in.n)-ones(indice_b:B_in.n)]
end

[H_out, B_out]=myconvex_hull_fix(W_in,H_in,B_in,indice_h-1)

endfunction
    

function [H_out, B_out]=myconvex_hull_fix(W_in,H_in,B_in,indice_h)

//IMPORTANTE: só funciona se H e B estiverem já consistentes, ou seja:
//Para o caso de novo ponto, este novo ponto já deve estar ordenado e os pontos
//tanto de H quanto de B que tiverem angulos maiores que ele devem ter seus indices
//incrementados.
//Semelhantemente, para o caso de remocao de pontos, todos os pontos de H e B com
//angulos maiores devem ter seus indices decrementados.

//Tem uma outra funcao que faz isso, mas não é aqui.

//indice_h é a posicao de H em que houve a quebra da casca convexa. Para o caso de adição
//B aumenta e eventualmente H diminui
//Para o caso de remocao H aumenta ou fica como está, Se H aumenta, Bi diminui, é claro.

//calcula o numero de pontos em B que serao testados
n=idx_circular(W_in.n-H_in.idxW(idx_circular(indice_h,H_in.n))-(W_in.n-H_in.idxW(idx_circular(indice_h+1,H_in.n))),W_in.n)-1

//faz um teste basico, se depois que retira o ponto e reordena os pontos de
//H continuam consecutivos, entao nao precisa fazer nada, pois nao existem
//pontos em B que possam entrar.

if n > 0 then
    idxB=[(H_in.idxW(indice_h)+1):H_in.idxW(indice_h)+n] //estes sao os indices de B que poderam entrar em H
    idxPoints=[H_in.idxW(idx_circular(indice_h-1,H_in.n)),H_in.idxW(indice_h),  idxB, H_in.idxW(idx_circular(indice_h+1,H_in.n))]
else
    H_out=H_in; B_out=B_in;
    return
end

// points são todos os pontos em ordem de angulo
points=W_in.coord(idxPoints,:)

// m will denote the number of points on the convex hull.
idxH=[1, 2]
not_idxH=[]

m=2
for i = 3:n+3
    // Find next valid point on convex hull.
    cross_prod = ccw(points(idxH(m-1),1:2), points(idxH(m),1:2), points(i,1:2))
    if cross_prod == 0
          idxH = [idxH i]//considera que se é colinear esta na hull
          m=m+1 
    elseif cross_prod > 0
          idxH = [idxH i]
          m=m+1 
    else
//        not_idxH_part=[]
        while cross_prod < 0 & m > 2
//              not_idxH_part=[idxH(m) not_idxH_part]
              idxH(m)=[]
              m=m-1
              cross_prod = ccw(points(idxH(m-1),1:2), points(idxH(m),1:2), points(i,1:2))        
        end
//        not_idxH=[not_idxH not_idxH_part]
        idxH = [idxH i]
        m=m+1
     end
end
nidxH=length(idxH)
newH=idxPoints(idxH(3:nidxH-1))

H_out.idxW=[H_in.idxW(1:indice_h) newH H_in.idxW(indice_h+1:H_in.n)]
H_out.n=H_in.n+nidxH-3

for i=1:nidxH-3
   B_in.idxW(find(B_in.idxW==newH(i)))=[]
end

B_out=B_in
B_out.n=B_in.n-(nidxH-3)

endfunction

function [cross_prod]=ccw(p1, p2, p3)
    cross_prod = (p2(1) - p1(1))*(p3(2) - p1(2)) - (p2(2) - p1(2))*(p3(1) - p1(1))
endfunction
