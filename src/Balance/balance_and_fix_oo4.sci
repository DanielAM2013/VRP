exec area_calc.sci
exec myconvex_hull.sci
exec myconvex_fix_add.sci
exec myconvex_hull_rem.sci

function [Areas_out, W_out, H_out, B_out]=balance_and_fix_oo4(n_wp, k, W, H, B, Areas)
//Esta versao balancea os angulos sempre fazendo movimentos que nao cruzem a desigualdade
//Outra diferença é que passa o angulo da area maior para a area menor, tranferindo
//de area em area.

//Encontra a classe de maior area e sua posicao na ordem das secoes no sentido anti horario
[max_area, cl_max]=max(Areas)
//Encontra a classe de menor area e sua posicao na ordem das secoes no sentido anti horario
[min_area, cl_min]=min(Areas)

propaga = cl_min - cl_max
//Se propaga > 0, cl_min > cl_max, o movimento é no sentido anti-horario, transferindo a partir do maior angulo
//Se propaga < 0, cl_min < cl_max, o movimento é no sentido horario, transferindo a partir do menor angulo

if propaga > 0
    for i=0:propaga-1
          this_class=cl_max+i
          new_class=this_class+1

          W(new_class).coord=[[0 0 0 0]; W(new_class).coord]
          W(new_class).coord(2,:)=W(this_class).coord(W(this_class).n,:)
          W(new_class).n=W(new_class).n+1
             
          W(this_class).coord(W(this_class).n,:)=[]
          W(this_class).n=W(this_class).n-1
             
          [H_t, B_t]=myconvex_fix_add(W(new_class), H(new_class), B(new_class),2)
          B(new_class)=B_t
          H(new_class)=H_t
             
          [H_t, B_t]=myconvex_hull_rem(W(this_class), H(this_class), B(this_class), W(this_class).n+1)
          B(this_class)=B_t
          H(this_class)=H_t  
    end
end

if propaga < 0
    for i=0:-1:propaga+1
          this_class=cl_max+i
          new_class=this_class+1

             this_class=cl_max+i
             new_class=this_class-1
             
             W(new_class).coord=[W(new_class).coord;W(this_class).coord(2,:)]
             W(new_class).n=W(new_class).n+1
             
             W(this_class).coord(2,:)=[]
             W(this_class).n=W(this_class).n-1
             [H_t, B_t]=myconvex_fix_add(W(new_class), H(new_class), B(new_class), W(new_class).n)
             B(new_class)=B_t,H(new_class)=H_t
             [H_t, B_t]=myconvex_hull_rem(W(this_class), H(this_class), B(this_class), 2)
             B(this_class)=B_t,H(this_class)=H_t
    end
end

W_out = W;
H_out=H;
B_out=B;

//re-calcula as areas

Areas_out=Areas
for i=1:k
  [Area1, Area2]= area_calc(W_out(i).coord(H_out(i).idxW,1),W_out(i).coord(H_out(i).idxW,2), W_out(i).coord(:,4), H_out(i).idxW)
   Areas_out(i)=Area1;
end


endfunction
