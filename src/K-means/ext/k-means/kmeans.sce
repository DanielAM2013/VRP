clear;
clc

	exec cost.sci;
	exec kmeans.sci;

	points=read('../arg/input.dat',-1,2);

	//calcula o angulo rho
	args = atan(points(:,2), points(:,1));

	//define qtd clusters
	k=5;

	//chama a função
	[classes, centers, sumd, D, err] = kmeans(wp_rho, k);

	for i=1:k
		membership = (classes == i);
		members = wp(membership, :);
		plot(members(:,1),members(:,2));
			last_line=gce();
			last_line.children.line_mode="off";
			last_line.children.mark_mode="on";
			last_line.children.mark_style=2;
			last_line.children.mark_foreground=i+1;
			last_line.children.mark_size=5;
	end 
