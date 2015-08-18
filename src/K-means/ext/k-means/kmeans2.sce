clear;
//clc;

exec kmeans.sci;
exec objCost.sci;
exec area_calc.sci;
exec pi22pi.sci
exec calc_gaps.sci;
exec balance.sci;    
exec plot_wp.sci;

data=100*read('../arg/input2.dat',50,2);

deg=%pi/180;

// Origem
Oidx=17
O=data(Oidx,:);

points=data-ones(size(data,1),1)*O;

n=size(points,1);

//calcula o angulo rho
args = atan(points(:,2), points(:,1));

//define qtd clusters
k=4;

// CALL kmeans
// classes: vetor indicando a classe de cada ponto
// centers: centros de cada subgrupo
// sumd: custo total do cluster
// D: distância ao quadrado de cada ponto ao centro de seu subgrupo
[classes, centers, sumd, D, err] = kmeans(args, k);

all = [classes points args [1:n]'];

while(1)

    plota_wp(all,k);
    //chama a funcao que faz o balanco das areas da casca convexa
    [all, area_sorted, length_vector] = balance(all, k);

	x=1;
	while(x~=10)
		position
		changing
		area_sorted

		for i=1:k	
			plot( maximus(i,2), maximus(i,3), minimus(i,2), minimus(i,3));
   			last_line=gce();
			last_line.children.line_mode="off";
			last_line.children.mark_mode="on";
			last_line.children.mark_foreground=5;
			last_line.children.mark_size=10;
		end
		plot( wp(swop,1), wp(swop,2));
		last_line=gce();
		last_line.children.mark_mode="on";
		last_line.children.mark_foreground=10;
		last_line.children.mark_size=5;

		x=input('pause :');
	end

	clf;

end
