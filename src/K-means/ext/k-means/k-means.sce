clear
clf

exec area_calc.sci;

exec kmeans.sci;
	
// calculate the sum of distances
exec objCost.sci;

// convert from -pi pi to 0 2pi
exec pi22pi.sci;

exec  calc_gaps.sci;

exec balance.sci;
     
exec plot_wp.sci;

// Exemplo de teste. Gera pontos em vários quadrantes e faz o clusters


data1=read('../arg/input2.dat',50,2);

deg=%pi/180;


O=data1(16,:);

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

//    disp('pause'),pause
    clf
end
