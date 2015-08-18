function [Areas_out, W_out, H_out, B_out]=balance_and_fix_oo3(n_wp, k, W, H, B, Areas)

//exec area_calc.sci
//exec myconvex_hull.sci
//exec myconvex_fix_add.sci
//exec myconvex_hull_rem.sci

//calcula a abertura das secoes e os espacos entre elas (ainda nao uso para nada)
//gaps_ord = calc_gaps(indexes(:,1:2))
//aberturav = wp_full(indexes(:,2),4) - wp_full(indexes(:,1),4);

//heuristica1 que passa para o vizinho menor o ponto mais proximo
//encontra a classe de maior area e sua posicao na ordem das secoes no sentido anti horario
[max_area, cl_max]=max(Areas)

//Lembrando que a ordem das secoes sao as mesmas das classes
Areas_circle=[Areas(k,:);Areas;Areas(1,:)];

//encontra o vizinho com casca convexa menor
[area_min, idx_min] = min(Areas_circle(1+cl_max-1),Areas_circle(1+cl_max+1))

class_circle=[k,1:k,1]';
new_class=class_circle(cl_max+1+(2*idx_min-3))

//verifica se os novos angulos de abertura nao vao exceder 180 graus
Point_transf_min=W(cl_max).coord(2,:)
if cl_max == 1 & new_class == k
    Point_transf_min(1,3)=360
end
new_apert1=(Point_transf_min(1,3) - W(new_class).coord(2,3))

Point_transf_max=W(cl_max).coord(W(cl_max).n,:)
if cl_max == k & new_class == 1
    Point_transf_max(1,3)=-360+Point_transf_max(1,3)
end
new_apert2=(W(new_class).coord(W(new_class).n,3) - Point_transf_max(1,3))

short=1
if (idx_min == 1 & new_apert1 > 180)  | (idx_min == 2 & new_apert2 > 180) //tem que transferir pelo outro lado!
//if (new_apert1 > 180)  | (new_apert2 > 180) //tem que transferir pelo outro lado!
    short=0
end

if short == 1 //faz a passagem do angulo diretamente para o vizinho
    if idx_min == 1
    //é a classe com menores angulos. Transfere o menor de uma para o maior da outra
             W(new_class).coord=[W(new_class).coord;W(cl_max).coord(2,:)]
             W(new_class).n=W(new_class).n+1
             W(cl_max).coord(2,:)=[]
             W(cl_max).n=W(cl_max).n-1
             //recalcula H  e Area para as classes afetadas
             [H_t, B_t]=myconvex_fix_add(W(new_class), H(new_class), B(new_class), W(new_class).n)
             B(new_class)=B_t
             H(new_class)=H_t
             [H_t, B_t]=myconvex_hull_rem(W(cl_max), H(cl_max), B(cl_max), 2)
             B(cl_max)=B_t
             H(cl_max)=H_t
    else //é a classe com maiores angulos. Transfere o maior de uma para o menor da outra
             W(new_class).coord=[[0 0 0 0]; W(new_class).coord]
             W(new_class).coord(2,:)=W(cl_max).coord(W(cl_max).n,:)
             W(new_class).n=W(new_class).n+1
             W(cl_max).coord(W(cl_max).n,:)=[]
             W(cl_max).n=W(cl_max).n-1
             [H_t, B_t]=myconvex_fix_add(W(new_class), H(new_class), B(new_class),2)
             B(new_class)=B_t
             H(new_class)=H_t
             [H_t, B_t]=myconvex_hull_rem(W(cl_max), H(cl_max), B(cl_max), W(cl_max).n+1)
             B(cl_max)=B_t
             H(cl_max)=H_t  
    end
    //trata a questao do angulo 0 ter mudado de dono. Se isso acontecer vai haver
    //inconsistencia entre minimos e maximos na forma como eu fiz o programa.
    //MAs tem que consertar esta minha gambiarra...
    if W(k).coord(W(k).n,3) == 0 //significa que o ponto com pho = 0 é agora o maior da ultima classe 
        //aplica uma nova rotacao para tras para que o minimo angulo da classe 1 seja sempre zero.
        //mantendo a classe com angulo zero sempre a mesma. Para tanto,
        //sempre que o indice de troca for o 1 (que é o do angulo =0)
        //faz com que ele seja 360 e faz nova rotacao.
        W(k).coord(W(k).n,3)=360;
        rot_rho=W(1).coord(2,3);
        for i=1:k
           W(i).coord(2:W(i).n,3) = W(i).coord(2:W(i).n,3) - rot_rho*ones(W(i).n-1,1)
        end
    end 
    if  W(1).coord(3,3) == 0
        //semelhantemente tem que ajustar pois significa que o angulo maior
        //agora pertence ao primeiro setor e com isso o angulo 0 deixa de ser o
        //limite inferior da 1a classe, passando a ser o proximo angulo. Faz-se rotacao para frente
        rot_rho = 360 - W(1).coord(2,3);
        for i=1:k
           W(i).coord(2:W(i).n,3) = W(i).coord(2:W(i).n,3) + rot_rho*ones(W(i).n-1,1)
        end
        W(1).coord(2,3)=0;  
    end
end
if short == 0 //se fizer a passagem do angulo diretamente para o visinho fica ruim. tem que passar por todos pelo outro lado
   if idx_min == 1 
    //é a classe com menores angulos. Transfere o maior para o menor até chegar nela, indo no sentido anti horario
      for j=0:k-2
             this_class=idx_circular(cl_max+j,k)
             new_class=idx_circular(this_class+1,k)
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
//       end
       if W(k).coord(W(k).n,3) == 0 
           W(k).coord(W(k).n,3)=360;
           rot_rho=W(1).coord(2,3);
           for i=1:k
                W(i).coord(2:W(i).n,3) = W(i).coord(2:W(i).n,3) - rot_rho*ones(W(i).n-1,1)
           end
       end
       if  W(1).coord(3,3) == 0
           rot_rho = 360 - W(1).coord(2,3);
           for i=1:k
               W(i).coord(2:W(i).n,3) = W(i).coord(2:W(i).n,3) + rot_rho*ones(W(i).n-1,1)
           end
           W(1).coord(2,3)=0;  
       end
     end
   elseif idx_min == 2 //é a classe com maiores angulos. Transfere o menor de uma para o maior até chegar nela
     for j=0:k-2
             this_class=idx_circular(cl_max-j,k)
             new_class=idx_circular(this_class-1,k)
             
             W(new_class).coord=[W(new_class).coord;W(this_class).coord(2,:)]
             W(new_class).n=W(new_class).n+1
             
             W(this_class).coord(2,:)=[]
             W(this_class).n=W(this_class).n-1
             [H_t, B_t]=myconvex_fix_add(W(new_class), H(new_class), B(new_class), W(new_class).n)
             B(new_class)=B_t,H(new_class)=H_t
             [H_t, B_t]=myconvex_hull_rem(W(this_class), H(this_class), B(this_class), 2)
             B(this_class)=B_t,H(this_class)=H_t
//      end
       if W(k).coord(W(k).n,3) == 0 
           W(k).coord(W(k).n,3)=360;
           rot_rho=W(1).coord(2,3);
           for i=1:k
                W(i).coord(2:W(i).n,3) = W(i).coord(2:W(i).n,3) - rot_rho*ones(W(i).n-1,1)
           end
       end
       if  W(1).coord(3,3) == 0
           rot_rho = 360 - W(1).coord(2,3);
           for i=1:k
               W(i).coord(2:W(i).n,3) = W(i).coord(2:W(i).n,3) + rot_rho*ones(W(i).n-1,1)
           end
           W(1).coord(2,3)=0;  
       end
      end
    end
end



W_out = W;
H_out=H;
B_out=B;
//re-calcula as areas

Areas_out=Areas

for i=1:k
   //[nH, indH,not_indH]=myconvex_hull(W_out(i).coord(:,1:3))
   //reordena para que o ponto de lançamento, ou o de menor angulo,
   //seja também o 1o ponto da casca convexa
//   [idx idx_pos]=min(indH)   
 //  indH = [indH(idx_pos:nH), indH(1:idx_pos-1) ]
  [Area1, Area2]= area_calc(W_out(i).coord(H_out(i).idxW,1),W_out(i).coord(H_out(i).idxW,2), W_out(i).coord(:,4), H_out(i).idxW)
   Areas_out(i)=Area1;
 //  B_out(i).idxW=not_indH
 //  B_out(i).n=length(not_indH)
end


endfunction
