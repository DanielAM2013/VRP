clear;	

exec fun/idx_circular.sci;
exec fun/area_calc.sci;
exec fun/ccw.sci;
exec fun/insert.sci;
exec fun/myconvex_hull.sci;
exec fun/myconvex_fix_add.sci;
exec fun/myconvex_hull_fix.sci;
exec fun/myconvex_hull_rem.sci;
exec fun/balance_and_fix_oo3.sci;
exec fun/balance_and_fix_oo4.sci;
exec fun/objCost.sci;
exec fun/kmeans.sci;
exec fun/pi22pi.sci;
exec fun/plota_wpoo.sci;
exec fun/wp_cond.sci;
exec fun/NormGrad.sci;

	data=read('dat/input.dat',-1,2);

	deg=%pi/180;

	// Oidx:= indice da origem em data
	Oidx=10;

	// k:= número de classes a dividir data
	k=4;

	condiciona=2;

	// O:= origem de data
	O=data(Oidx,:);

	data(Oidx,:)=[];

	// n:= número de pontos em data sem a origem
	n=size(data,1);

	// wp:= data deslocado de O
	wp=data-ones(n,1)*O;

//-----------------------------------------------------------------------------
//! Tratamento dos pontos iniciais

	// norm_wp:= norma dos vetores de wp
	for i=1:n
		norm_wp(i)=norm(wp(i,1:2),2);
	end

	// min_norm:= menor norma de norm_wp
	min_norm=min(norm_wp);

	// Reescala para que as normas sejam maiores que a unidade
	wp=wp/min_norm;

	// calcula o angulo rho sempre entre 0 e 360 em graus
	rho_wp = pi22pi(atan(wp(:,2), wp(:,1)))/deg;

	wp = [wp rho_wp norm_wp/min_norm];

	//ordena wp_full a partir do angulo menor para o maior que deve ser sempre
	//menor ou igual a 360. Isso forca que as classes estejam agrupadas
	[trash, ord_rho]=gsort(wp(:,3),'g','i');
	wp=wp(ord_rho,:);

	//melhor condiciona os pontos fazendo duas coisas: agrupando os angulos
	//muito proximos em apenas um, sendo que o angulo resultante o relacionado
	//com o mais distante, mantendo os dois pontos. Caso a diferenca de
	//distancia esteja dentro da cobertura da camera, entao o ponto resultante
	//um novo ponto que é a media de todos. Um novo angulo é entao calculado.

	wp = [wp [1:n]'];
//-----------------------------------------------------------------------------
//!----------------------------------------------------------------------------
	// operador merge: faz o merge entre dois pontos proximos. Esta operacao
	// substitui dois pontos de passagem pela media deles. A distancia afast_max
	// é a metade ma menor distancia da projetcao de uma camera no solo.

	afast_max = 3;
	if condiciona == 1 
		[wp, n]=wp_cond(wp, n, afast_max);
	end
//-----------------------------------------------------------------------------
//!----------------------------------------------------------------------------
	//Calcula o espacamento entre os pontos para que o angulo zero seja o de
	//maior espacamento com o seu vizinho anterior
	gaps=zeros(n,1);
	gaps(1)=modulo(360+wp(1,3)-wp(n,3),360);
	for i=2:n
        gaps(i)=wp(i,3)-wp(i-1,3);
	end

	// localiza o maior espaçamento e o coloca no início de todos os angulos
	[max_gap, idxG]=max(gaps);
	wp=[wp(idxG:n,:);wp(1:idxG-1,:)];
//-----------------------------------------------------------------------------

	//rotaciona todos os angulos para que o 1o seja 0
	ref_rot=wp(1,3);
	wp(:,3)=NormGrad(wp(:,3)-ref_rot*ones(n,1));

	//So calcula classes, ordena, etc, se k>1
	//chama a função kmeans
	[classes, centers, sumd, D, err] = kmeans(wp(:,3), k);

	exec fun/insert.sci;
	exec fun/convex_merger.sci;
	exec fun/perimeter.sci;
	exec fun/convexo.sci;

	for sel=0:1
		clf;
		eval=0;
	for i=1:k
		points=[ 0 0; wp(classes==i,1:2)];
		[cluster(i).cvx, cluster(i).idx]=convexo(points,sel);
		idx_plot=[cluster(i).cvx(1).ind cluster(i).cvx(1).ind(1)];
		set_plot=points(idx_plot,:);
		plot(set_plot(:,1),set_plot(:,2));
		idx_plot=[cluster(i).idx  cluster(i).idx(1)];
		set_plot=points(idx_plot,:);
		plot(set_plot(:,1),set_plot(:,2),'rx-');
		eval=eval+perimeter(points(cluster(i).idx,:));
	end
		disp(eval);
		x=sprintf('fig/vrp%d',sel+1);
		xs2png(0,x);
	end
