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
clf

function p_area = area_calc(x,y)
// Get the number of vertices
n = length(x);

//inverte a ordem dos indices, pois aparentemente esta funcao usa ordenacao
//clockwise e o que eu tenho é ordenacao counterclockwise

xold=x;
yold=y;

for i = 1 : n
    x(n) = xold(n-i+1);
end

// Initialize the area
p_area = 0;

// Apply the formula)
for i = 1 : n-1
    p_area = p_area + (x(i) + x(i+1)) * (y(i) - y(i+1));
end
p_area = abs(p_area)/2;
endfunction

function [classes, centers, sumd, D, err] = kmeans(data, k)

  // defaults for options
  emptyaction = "error";
  start       = "sample";
  
  //used for getting the number of samples
  nRows = max(size(data));

  // used to hold the distances from each sample to each class
  D = zeros (nRows, k);

  //used for convergence of the centroids
  err = 1;

  //initial sum of distances
  sumd = %inf;

  while 1 
      idx = round(rand(1,k)*nRows);
      if idx(1) ~= idx(2) then
          break
      end
  end
  
  centers = data (idx, :);

  // Run the algorithm
 while err > .000001
    // Compute squared distances
    for i = 1:k
       centroid = centers(i,:);
       for j=1:nRows
           diff_vector = data(j,:)-centroid;
           dist_j = (norm(diff_vector))^2;
           D(j,i) = dist_j;
       end
    end

    // Classify
    [minD, classes] = min(D,'c');
     cluster = [minD,classes,idx(classes)'];
     
    // Calculate new centroids
    for i = 1:k
      // Get binary vector indicating membership in cluster i
      membership = (classes == i);
      // update the centroids
      elementos = data(membership, :);
      centers(i, :) = sum(elementos,1)/size(elementos,1);
    end

    // calculate the difference in the sum of distances
    err  = sumd - objCost (data, classes, centers);
    // update the current sum of distances
    sumd = objCost (data, classes, centers);
  end
endfunction

// calculate the sum of distances
function obj = objCost (data, classes, centers)
  obj = 0;
    for i=1:max(size(data))
       sumsq = 0;
       for j = 1:min(size(data))
           sumsq = sumsq + (data(i,j) - centers(classes(i),j))^2;
       end
       obj = obj + sumsq;
    end
endfunction

// convert from -pi pi to 0 2pi
function angle = pi22pi(angle)
[n,m]=size(angle);
for i =1:n
    for j = 1:m
        if angle(i,j) < 0, angle(i,j) = angle(i,j) + 2*%pi, end
    end
end
endfunction

function espacos = calc_gaps(extremos_ord)
          //calcula os espacos entre as secoes
      
n=length(extremos_ord(:,1));
extremos_ord_cicle = [extremos_ord;extremos_ord(1,:)]
espacos=[];
for i=1:n
   espacoi=extremos_ord_cicle(i+1,1)-extremos_ord_cicle(i,2);
   if espacoi < 0,espacoi = 360 + espacoi;end
   espacos = [espacos espacoi];
end
endfunction      
      
function [wp_new, wp_ord, n_wpv]=balance(wp_full, k)

n_wp=length(wp_full(:,1))
wp=wp_full(:,2:3);

//ordena as classes
wp_ord = []

n_wpv=[];
for i=1:k
    n_wpi=0;
    for j=1:n_wp
      if wp_full(j,1) == i;
          wp_ord = [wp_ord; wp_full(j,:)]
          n_wpi=n_wpi+1;
      end
    end
    n_wpv=[n_wpv;n_wpi];
end

//separa as classes
aberturav=[];
minimus = [];
maximus = [];
Area0v = [];
for i=1:k
     class_init = sum(n_wpv(1:i-1));
     class_fim = class_init + n_wpv(i);
     wpi=wp_ord(class_init+1:class_fim, :);
//     wp_rho_gradi=wpi(:,4)/deg;
     [min_rhoi,indexmini] = min(wpi(:,4));
     [max_rhoi,indexmaxi] = max(wpi(:,4));
      minimus = [minimus;[wpi(indexmini,:),indexmini]];
      maximus = [maximus;[wpi(indexmaxi,:),indexmaxi]];
      aberturai = max_rhoi-min_rhoi;
      aberturav=[aberturav aberturai];
      wpi0=[wpi(:,2:3);[0 0]];
      [nhulli, indi]=convex_hull(wpi0');
      hullix=wpi0(indi,1);
      hulliy=wpi0(indi,2);
      Areai0 = area_calc(hullix,hulliy);
      Area0v = [Area0v;Areai0];
end

//ordena os setores para sempre contarem crescente no sentido anti-horario
boundariesPI=[minimus(:,4) maximus(:,4)];
boundariesDEG=pi22pi(boundariesPI)/deg;
[min_ord,ord_sec]=gsort(boundariesDEG(:,1),'g','i');
boundaries_ord = boundariesDEG(ord_sec,:);

//calcula os espacos entre as secoes
      
gaps_ord = calc_gaps(boundaries_ord)
      
Area0_ordered=[[1:k]' Area0v];
Area0_ordered=Area0_ordered(ord_sec,:)
Area0_circle=[Area0_ordered(k,:);Area0_ordered;Area0_ordered(1,:)];

//heuristica1 que passa para o vizinho menor o ponto mais proximo

//encontra a classe de maior area e sua posicao na ordem das secoes no sentido anti horario
[max_area0, position_area0_max]=max(Area0_ordered(:,2))
//class_area0_max=Area0_indexed(max_index_area0,2)
class_area0_max=Area0_ordered(position_area0_max,1)

//encontra o vizinho menor
[neighbour_min, index_neighbour_max] = min(Area0_circle(1+position_area0_max-1,2),Area0_circle(1+position_area0_max+1,2))
neighbour_rel=[-1 1];
changing_neighbour_area=Area0_circle(1+position_area0_max+neighbour_rel(index_neighbour_max),:)
class_changing_area=changing_neighbour_area(1)
 
if (neighbour_rel(index_neighbour_max))==-1 //é a classe mais à frente do relogio. passa o minimo_pho para a outra classe
     for i=1:n_wp
     if wp(i,:) == minimus(class_area0_max,2:3)
       indice_troca=i;
     end
     end
elseif (neighbour_rel(index_neighbour_max))==1 //é a classe mais à frente do relogio. passa o minimo_pho para a outra classe
     for i=1:n_wp
     if wp(i,:) == maximus(class_area0_max,2:3)
       indice_troca=i;
     end
     end
end
wp_full(indice_troca,1)=class_changing_area;
wp_new = wp_full;

endfunction

function plota_wp(wp_full,k)
    
    classes=wp_full(:,1);
    wp=wp_full(:,2:3);
    wp_rho=wp_full(:,4);
    Area = zeros(1,k);

      membership1 = (classes == 1);
      elementos1 = wp(membership1, :);
      elementos_rho1 = wp_rho(membership1, :);
      elementos_rho_grad1 = elementos_rho1*180/%pi;
      [min_rho1,indexmin1] = min(elementos_rho_grad1);
      [max_rho1,indexmax1] = max(elementos_rho_grad1);
      abertura_1 =max_rho1-min_rho1;
      plot(elementos1(:,1),elementos1(:,2),'xr')      
      elementos10 = [elementos1;[0 0]];
      [nhull1, ind1]=convex_hull(elementos10');
      hull1x=elementos10(ind1,1);
      hull1y=elementos10(ind1,2);
      Area10 = area_calc(hull1x,hull1y);
      
      Area(1)=Area10;
            
      plot([hull1x;hull1x(1)],[hull1y;hull1y(1)],'r')
          
      membership2 = (classes == 2);
      elementos2 = wp(membership2, :);
      elementos_rho2 = wp_rho(membership2, :);
      elementos_rho_grad2 = elementos_rho2*180/%pi;
      [min_rho2,indexmin2] = min(elementos_rho_grad2);
      [max_rho2,indexmax2] = max(elementos_rho_grad2);
      abertura_2 =max_rho2-min_rho2;
      plot(elementos2(:,1),elementos2(:,2),'xg')  
      elementos20 = [elementos2;[0 0]];
      [nhull2, ind2]=convex_hull(elementos20');
      hull2x=elementos20(ind2,1);
      hull2y=elementos20(ind2,2);
      Area20 = area_calc(hull2x,hull2y);
      
      Area(2)=Area20;
            
      plot([hull2x;hull2x(1)],[hull2y;hull2y(1)],'g')
      
      membership3 = (classes == 3);
      elementos3 = wp(membership3, :);
      elementos_rho3 = wp_rho(membership3, :);
      elementos_rho_grad3 = elementos_rho3*180/%pi;
      [min_rho3,indexmin3] = min(elementos_rho_grad3);
      [max_rho3,indexmax3] = max(elementos_rho_grad3);
      abertura_3 =max_rho3-min_rho3;
      plot(elementos3(:,1),elementos3(:,2),'xb')      
      elementos30 = [elementos3;[0 0]];
      [nhull3, ind3]=convex_hull(elementos30');
      hull3x=elementos30(ind3,1);
      hull3y=elementos30(ind3,2);
      Area30 = area_calc(hull3x,hull3y);

      Area(3)=Area30;
      
      plot([hull3x;hull3x(1)],[hull3y;hull3y(1)],'b')
          
      membership4 = (classes == 4);
      elementos4 = wp(membership4, :);
      elementos_rho4 = wp_rho(membership4, :);
      elementos_rho_grad4 = elementos_rho4*180/%pi;
      [min_rho4,indexmin4] = min(elementos_rho_grad4);
      [max_rho4,indexmax4] = max(elementos_rho_grad4);
      abertura_4 =max_rho4-min_rho4;
      plot(elementos4(:,1),elementos4(:,2),'xy')
      elementos40 = [elementos4;[0 0]];
      [nhull4, ind4]=convex_hull(elementos40');
      hull4x=elementos40(ind4,1);
      hull4y=elementos40(ind4,2);
      Area40 = area_calc(hull4x,hull4y);

      Area(4)=Area40;

      plot([hull4x;hull4x(1)],[hull4y;hull4y(1)],'y')
      plot(0,0,'ob')

      total_abertura = abertura_1 + abertura_2 + abertura_3 + abertura_4;
      ganho_k4 = 360/total_abertura
      ganho1_k4 = 360 - total_abertura

endfunction

// Exemplo de teste. Gera pontos em vários quadrantes e faz o clusters

//Primeiro quadrante
//C1 = rand(100, 1);
//C2 = rand(100, 1);
//Segundo quadrante
//C3 = -1*rand(100, 1);
//C4 = rand(100, 1);
//Terceiro quadrante
//C5 = -1*rand(100, 1);
//C6 = -1*rand(100, 1);
//Quarto quadrante
//C7 = rand(100, 1);
//C8 = -1*rand(100, 1);

//wp = [C1 C2;C3 C4;C5 C6;C7 C8];
//wp = [C1 C2]; //Para o Emory: Apenas 1o quadrante

//data=[-600,808; -1028,509;-1129,660;-1373,291;-1702,602;-1828,1113;-1280,1122;-1739,1387;-1493,1802;-1019,1608;-397,1510;-117,1744;-55,925;-868,1199;-240,399];
data1=[-59.963495,-3.107272;
-59.941129,-3.122470;
-59.975596,-3.134267;
-59.940312,-3.129766;
-59.977537,-3.083593;
-59.970442,-3.109629;
-59.958660,-3.122203;
-59.949317,-3.124904;
-59.958816,-3.104909;
-59.942586,-3.114195;
-59.949439,-3.124031;
-59.983938,-3.122003;
-59.941184,-3.086237;
-59.953371,-3.088080;
-59.961682,-3.127137;
-59.956347,-3.110163;
-59.954570,-3.134279;
-59.990484,-3.106577;
-59.958281,-3.083266;
-59.944798,-3.083897;
-59.971464,-3.088919;
-59.989060,-3.124341;
-59.971182,-3.083225;
-59.966072,-3.091478;
-59.983611,-3.083098;
-59.985067,-3.117760;
-59.961701,-3.086151;
-59.950326,-3.122106;
-59.988124,-3.111986;
-59.961060,-3.112798;
-59.944899,-3.102907;
-59.959124,-3.126509;
-59.955024,-3.108570;
-59.969775,-3.102708;
-59.964543,-3.122406;
-59.989263,-3.123674;
-59.969953,-3.089108;
-59.950272,-3.131424;
-59.944839,-3.094235;
-59.955272,-3.125446;
-59.965144,-3.081551;
-59.945640,-3.093440;
-59.937483,-3.079945;
-59.969869,-3.105067;
-59.939803,-3.078707;
-59.959553,-3.084030;
-59.988477,-3.093803;
-59.980312,-3.127778;
-59.952424,-3.096602;
-59.940945,-3.103188];

//data = wp;

deg=%pi/180;

//O=[-59.956347,-3.110163];

O=data1(16,:);

//O = data(Oidx,:);
//wp = zeros(data);

for i=1:max(size(data1))
   wp(i,:) = data1(i,:) - O;
   if norm(wp(i,:))==0, Oidx=i,end
end

wp(Oidx,:)=[];
//wp=wp*1000000; //so para ajustar escala para este caso

//calcula o angulo rho
wp_rho = atan(wp(:,2), wp(:,1));

//define qtd clusters
k=4;

//chama a função kmeans
[classes, centers, sumd, D, err] = kmeans(wp_rho, k);

n_wp = length(classes);
wp_full = [classes wp wp_rho [1:n_wp]'];

while(1)

    //plota a condicao inicial
    plota_wp(wp_full,k)
      
    //chama a funcao que faz o balanco das areas da casca convexa
    [wp_full, wp_ord, length_vector] = balance(wp_full, k);

    disp('pause'),pause
    clf
end
