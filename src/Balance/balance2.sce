// Copyright (C) 2011 Soren Hauberg <soren@hauberg.org>
// Copyright (C) 2012 Daniel Ward <dwa012@gmail.com>
// Adapted to Scilab without arg in validation by Reginaldo Carvalho <joserhc@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, see <http://www.gnu.org/licenses/>.

// -*- texinfo -*-
// @deftypefn {Function File} {[@var{idx}, @var{centers}] =} kmeans (@var{data}, @var{k}, @var{param1}, @var{value1}, @dots{})
// K-means clustering.
//
// @seealso{linkage}
// @end deftypefn

clear
//clf

exec balance_and_fix_oo4.sci
exec area_calc.sci
exec kmeans.sci
exec pi22pi.sci
exec myconvex_hull.sci
exec myconvex_hull_rem.sci
exec wp_cond.sci
exec NormGrad.sce
//exec myconvex_fix_add.sci //refaz a casca convexa a partir da entrada de um ponto com angulo extremo aos existentes

function plota_wpoo(W,H,k)
    
cores = ['rx' 'r';'gx' 'g';'bx' 'b';'yx' 'y';'cx' 'c';'mx' 'm'];

for i=1:k
      n=size(H(i).idxW,2)
      plot(W(i).coord(:,1),W(i).coord(:,2),cores(i,1))      
      if n>0,plot([W(i).coord(H(i).idxW(n),1);,W(i).coord(H(i).idxW,1)],[W(i).coord(H(i).idxW(n),2);,W(i).coord(H(i).idxW,2)],cores(i,2)),end      
end            

endfunction

data=read('../arg/input2.dat',-1,2);

//data=[-59.963495,-3.107272;
//-59.941129,-3.122470;
//-59.975596,-3.134267;
//-59.940312,-3.129766;
//-59.977537,-3.083593;
//-59.970442,-3.109629;
//-59.958660,-3.122203;
//-59.949317,-3.124904;
//-59.958816,-3.104909;
//-59.942586,-3.114195;
//-59.949439,-3.124031;
//-59.983938,-3.122003;
//-59.941184,-3.086237;
//-59.953371,-3.088080;
//-59.961682,-3.127137;
//-59.956347,-3.110163;
//-59.954570,-3.134279;
//-59.990484,-3.106577;
//-59.958281,-3.083266;
//-59.944798,-3.083897;
//-59.971464,-3.088919;
//-59.989060,-3.124341;
//-59.971182,-3.083225;
//-59.966072,-3.091478;
//-59.983611,-3.083098;
//-59.985067,-3.117760;
//-59.961701,-3.086151;
//-59.950326,-3.122106;
//-59.988124,-3.111986;
//-59.961060,-3.112798;
//-59.944899,-3.102907;
//-59.959124,-3.126509;
//-59.955024,-3.108570;
//-59.969775,-3.102708;
//-59.964543,-3.122406;
//-59.989263,-3.123674;
//-59.969953,-3.089108;
//-59.950272,-3.131424;
//-59.944839,-3.094235;
//-59.955272,-3.125446;
//-59.965144,-3.081551;
//-59.945640,-3.093440;
//-59.937483,-3.079945;
//-59.969869,-3.105067;
//-59.939803,-3.078707;
//-59.959553,-3.084030;
//-59.988477,-3.093803;
//-59.980312,-3.127778;
//-59.952424,-3.096602;
//-59.940945,-3.103188];
//
//data=[0 0;0 1;0 2;0 3;0 4;0 5;1 0;1 1;1 2;1 3;1 4;1 5;2 0;2 1;2 2;2 3;2 4;2 5;3 0;3 1;3 2;3 3;3 4;3 5]

deg=%pi/180;

data1=data

////MUDA O PONTO DE DECOLAGEM AQUI!!!!////
Oidx=16;

O=data1(Oidx,:);
data1(Oidx,:)=[]

////MUDA O O NUMERO DE VANTS AQUI!!!!////
k=4;

condiciona =1

n_wp=size(data1,1)

for i=1:n_wp
   wp(i,:) = data1(i,:) - O;
end

//ajusta a escala para que o maior seja maior que um
if min(abs(wp(:,1:2))) > 0
    wp(:,1:2)=wp(:,1:2)/min(abs(wp(:,1:2)))
end

//calcula o angulo rho sempre entre 0 e 360 em graus
wp_rho = atan(wp(:,2), wp(:,1));
wp_rho=pi22pi(wp_rho)/deg

//calcula a distancia ate o ponto a partir do lancamento
wp_dist = sqrt(wp(:,1).^2 + wp(:,2).^2)
wp = [wp wp_rho wp_dist];

//aplica uma rotacao para que o minimo angulo seja zero.
//com isso o maior angulo é menor que 360, colocando a
//descontinuidade em um gap. Esta operacao tem que ser repetida sempre que houver uma troca
//de classe do angulo 0, que deve ser sempre a classe um (por convencao)
//min_wp_rho=min(wp_rho)
//wp_rho = wp_rho - min_wp_rho*ones(wp_rho)

//ordena a partir do angulo menor para o maior
//que deve ser sempre menor ou igual a 360. Isso forca que as classes
//estejam agrupadas

[counter_clock,ord_rho]=gsort(wp(:,3),'g','i');
wp=wp(ord_rho,:);

wp = [wp [1:n_wp]'];
wp_original = wp;

//condiciona os pontos
afast_max = 3;
if condiciona == 1 
   [wp, n_wp]=wp_cond(wp, n_wp, afast_max)
end

//Calcula o espacamento entre os pontos para que o angulo zero seja o de maior espacamento
//com o seu vizinho anterior
gaps=zeros(n_wp,1)
gaps(1)=360-wp(n_wp,3)+wp(1,3)
for i=2:n_wp
    gaps(i)=wp(i,3)-wp(i-1,3)
end
//localiza o maior espaçamento e faz deste o início de todos os angulos

[max_gap, idx_gap]=max(gaps)
wp=[wp(idx_gap:n_wp,:);wp(1:idx_gap-1,:)]

//rotaciona todos os angulos para que o 1o seja 0

ref_rot=wp(1,3)
wp(:,3)=NormGrad(wp(:,3)-ref_rot*ones(n_wp,1))

//So calcula classes, ordena, etc, se k>1
if k > 1  then
  //chama a função kmeans
  [classes, centers, sumd, D, err] = kmeans(wp(:,3), k);
  //wp_full = [classes wp];
  
  //encontra os indices minimos e maximos de cada classe
  indexes=zeros(k,3)
  gaps = zeros(k,1)
  indexes(1,1)=min(find(classes==1))
  indexes(k,2)=max(find(classes==k))
  gaps(1)=360+(wp(indexes(1,1),3)-wp(indexes(k,2),3))
  for i=1:k-1
      indexes(i,2)=max(find(classes==i))
      indexes(i+1,1)=min(find(classes==i+1))
      gaps(i+1)=wp(indexes(i+1,1),3)-wp(indexes(i,2),3)
  end
  indexes(:,3)=indexes(:,2)-indexes(:,1)+1
  
  [counter_clock,ord_class]=gsort(indexes(:,1),'g','i')
  indexes=indexes(ord_class,:)
      
  [max_gap, idx_gap]=max(gaps)
  idx_class=[idx_gap:k 1:idx_gap-1]'
  indexes_ord=indexes(idx_class,:)
  
  wp_ord=zeros(n_wp,6);
  idx_line=indexes(idx_class(1),:)
  wp_ord(1:idx_line(3),:)=[ones(idx_line(3),1) [wp(idx_line(1):idx_line(2),:)]]
  idx_last=idx_line(3)
  for i=2:k
      idx_line=indexes(idx_class(i),:)
      wp_ord(idx_last+1:idx_last+idx_line(3),:)=[i*ones(idx_line(3),1) [wp(idx_line(1):idx_line(2),:)]]
      idx_last=idx_last+idx_line(3)
  end
  
   //aplica uma rotacao para que o minimo angulo seja zero.
   //com isso o maior angulo é menor que 360, colocando a
   //descontinuidade em um gap.
   // esta operacao tem que ser repetida sempre que houver uma troca
   //de classe do angulo 0, que deve ser sempre a classe um (por convencao)
     min_wp_rho=min(wp_ord(:,4))
     wp_ord(:,4) = wp_ord(:,4) - min_wp_rho*ones(n_wp,1)
     wp_full=wp_ord

//As classes ja estao agrupadas. Faz agora usando as structs

for i=1:k
    W(i).coord=[[0 0 0 0];wp_full(indexes(i,1):indexes(i,2),2:5)]
    W(i).n=indexes(i,3)+1;
end

//Calcula a casca convexa a suas areas das classes iniciais para poder chamar a
//funcao que faz o balanceamento

Areas_v=[]
minmaxv=[]

Areas = zeros(k,1);

for i=1:k
//   [nH, indH]=convex_hull(W(i).coord(:,1:2)')
   [nH, indH,not_indH]=myconvex_hull(W(i).coord(:,1:3))
//   pause
   //reordena para que o ponto de lançamento, ou o de menor angulo,
   //seja também o 1o ponto da casca convexa
   [idx idx_pos]=min(indH)   
   indH = [indH(idx_pos:nH), indH(1:idx_pos-1) ]

   H(i).idxW=indH;
   H(i).n=nH
   B(i).idxW=not_indH
   B(i).n=W(i).n-nH
   [Area1, Area2]= area_calc(W(i).coord(H(i).idxW,1),W(i).coord(H(i).idxW,2), W(i).coord(:,4), H(i).idxW)
   Areas(i)=Area1;   
end
minmax=max(Areas)-min(Areas)

plota_wpoo(W, H,k)


minmax_opt = minmax;
W_opt=W
H_opt=H
Areas_opt=Areas

Areas_v=[Areas_v Areas_opt]
minmaxv=[minmaxv minmax_opt]
     
//chama a funcao que faz o balanco das areas da casca convexa
//Com a ordenação a partir do maior espaçamento, esta versao faz
//o balanceamento apenas por dentro, sem cruzar a descontinuidade.


[Areas,W,H,B] = balance_and_fix_oo4(n_wp, k, W, H, B, Areas);
minmax=max(Areas)-min(Areas)

clf

plota_wpoo(W, H,k)


it=1

while sum(Areas-Areas_opt) <> 0 & it <= 100

   if minmax < minmax_opt  then
     clf
     minmax_opt = minmax;
     W_opt=W
     Areas_opt=Areas  
     H_opt=H
     Areas_v=[Areas_v Areas_opt]
     minmaxv=[minmaxv minmax_opt]
	plota_wpoo(W_opt, H_opt,k);
   end
   [Areas,W,H,B] = balance_and_fix_oo4(n_wp, k, W, H, B, Areas);
   minmax=max(Areas)-min(Areas)
   it=it+1
end

elseif k == 1
    indexes=[1 n_wp n_wp]
     wp_full = [ones(n_wp,1) wp];
     //se so tiver uma classe, apenas faz com que o ang(1) seja 0
     min_wp_rho=min(wp_full(:,4))
     wp_full(:,4) = wp_full(:,4) - min_wp_rho*ones(n_wp,1)
     
     W(k).coord=[[0 0 0 0];wp_full(indexes(k,1):indexes(k,2),2:5)]
     W(k).n=indexes(k,3)+1;
     [nH, indH,not_indH]=myconvex_hull(W(k).coord(:,1:3))
     [idx idx_pos]=min(indH)   
     indH = [indH(idx_pos:nH), indH(1:idx_pos-1) ]

     H(k).idxW=indH;
     H(k).n=nH
     B(k).idxW=not_indH
     B(k).n=W(k).n-nH
   
     W_opt=W
     H_opt=H
     [Area1, Area2]= area_calc(W(k).coord(H(k).idxW,1),W(k).coord(H(k).idxW,2), W(k).coord(:,4), H(k).idxW)
     Areas_opt=Area1;
     
else
    disp('Erro: número de VANTs inválido'), return
end

plota_wpoo(W_opt, H_opt,k)




