clear;

exec balance_and_fix_oo4.sci;
exec area_calc.sci;
exec kmeans.sci;
exec pi22pi.sci;
exec myconvex_hull.sci;
exec myconvex_hull_rem.sci;
exec wp_cond.sci;
exec NormGrad.sce;
//exec myconvex_fix_add.sci //refaz a casca convexa a partir da entrada de um ponto com angulo extremo aos existentes
exec plota_wpoo.sci;

	data=read('arg/input3.dat',-1,2);

	deg=%pi/180;

	Oidx=16;

	O=data(Oidx,:);
	data(Oidx,:)=[];

	k=4;

	condiciona=1;

	n_wp=size(data,1);

	for i=1:n_wp
		wp(i,:)=data(i,:)-O;
		norm_wp(i)=norm(wp(i,:));
	end

	//ajusta a escala para que o maior seja maior que um
	min_norm=min(norm_wp);
	wp_norm=wp/min_norm;

	//calcula o angulo rho sempre entre 0 e 360 em graus
	wp_rho = modulo(360+atan(wp(:,2), wp(:,1))/deg,360);

	//calcula a distancia ate o ponto a partir do lancamento
	wp_dist = norm_wp/min_norm;
	wp = [wp_norm wp_rho wp_dist];

	//aplica uma rotacao para que o minimo angulo seja zero.  com isso o maior
	//angulo é menor que 360, colocando a descontinuidade em um gap. Esta
	//operacao tem que ser repetida sempre que houver uma troca de classe do
	//angulo 0, que deve ser sempre a classe um (por convencao)
	//min_wp_rho=min(wp_rho) wp_rho = wp_rho - min_wp_rho*ones(wp_rho)

	//ordena a partir do angulo menor para o maior que deve ser sempre menor ou
	//igual a 360. Isso forca que as classes estejam agrupadas

	[counter_clock,ord_rho]=gsort(wp_rho,'g','i');
	wp=wp(ord_rho,:);

	wp = [wp [1:n_wp]'];

	//condiciona os pontos
	afast_max = 3;
	if condiciona == 1 
   		[wp, n_wp]=wp_cond(wp, n_wp, afast_max);
	end

	//Calcula o espacamento entre os pontos para que o angulo zero seja o de
	//maior espacamento com o seu vizinho anterior

	gaps=zeros(n_wp,1);
	gaps(1)=360-wp(n_wp,3)+wp(1,3);
	for i=2:n_wp
	    gaps(i)=wp(i,3)-wp(i-1,3);
	end

	//localiza o maior espaçamento e faz deste o início de todos os angulos
	[max_gap, idx_gap]=max(gaps);
	wp=[wp(idx_gap:n_wp,:);wp(1:idx_gap-1,:)];

	//rotaciona todos os angulos para que o 1o seja 0
	ref_rot=wp(1,3);
	wp(:,3)=NormGrad(wp(:,3)-ref_rot*ones(n_wp,1));

	//So calcula classes, ordena, etc, se k>1
	if k > 1  then

		//chama a função kmeans
		[classes, centers, sumd, D, err] = kmeans(wp(:,3), k);
  
		//encontra os indices minimos e maximos de cada classe
		indexes=zeros(k,3);
		gaps = zeros(k,1);
		indexes(1,1)=min(find(classes==1));
		indexes(k,2)=max(find(classes==k));
		gaps(1)=modulo(360+(wp(indexes(1,1),3)-wp(indexes(k,2),3)),360);
		for i=1:k-1
			indexes(i,2)=max(find(classes==i));
			indexes(i+1,1)=min(find(classes==i+1));
      		gaps(i+1)=modulo(360+wp(indexes(i+1,1),3)-wp(indexes(i,2),3),360);
		end
		indexes(:,3)=indexes(:,2)-indexes(:,1)+1;
  
//		[counter_clock,ord_class]=gsort(indexes(:,1),'g','i');
//		indexes=indexes(ord_class,:);
      
		[max_gap, idx_gap]=max(gaps);
		idx_class=[idx_gap:k 1:idx_gap-1]';
		indexes_ord=indexes(idx_class,:);
  
		wp_ord=zeros(n_wp,6);
		for i=1:k
			idx_line=indexes(idx_class(i),:);
			wp_ord(idx_line(1):idx_line(2),:)=[i*ones(idx_line(3),1) [wp(idx_line(1):idx_line(2),:)]];
		end
  
		//aplica uma rotacao para que o minimo angulo seja zero.  com isso o
		//maior angulo é menor que 360, colocando a descontinuidade em um gap.
		//esta operacao tem que ser repetida sempre que houver uma troca de
		//classe do angulo 0, que deve ser sempre a classe um (por convencao)
		min_wp_rho=min(wp_ord(:,4));
		wp_ord(:,4) = wp_ord(:,4) - min_wp_rho*ones(n_wp,1);
		wp_full=wp_ord;

		//As classes ja estao agrupadas. Faz agora usando as structs
		for i=1:k
    		W(i).coord=[[0 0 0 0]; wp_full(indexes(i,1):indexes(i,2),2:5)];
			W(i).n=indexes(i,3)+1;
		end

		//Calcula a casca convexa a suas areas das classes iniciais para poder
		//chamar a funcao que faz o balanceamento
		Areas_v=[];
		minmaxv=[];

		Areas = zeros(k,1);

		for i=1:k
			[nH, indH,not_indH]=myconvex_hull(W(i).coord(:,1:2));
			//reordena para que o ponto de lançamento, ou o de menor angulo,
			//seja também o 1o ponto da casca convexa
			[idx idx_pos]=min(indH); 
			indH = [indH(idx_pos:nH), indH(1:idx_pos-1) ];
			H(i).idxW=indH;
			H(i).n=nH;
			B(i).idxW=not_indH;
			B(i).n=W(i).n-nH;
			[Area1, Area2]=area_calc(W(i).coord(indH,1),W(i).coord(indH,2),W(i).coord(:,4),indH);
			Areas(i)=Area1;
		end
		minmax=max(Areas)-min(Areas);

		minmax_opt = minmax;
		W_opt=W;
		H_opt=H;
		Areas_opt=Areas;

		Areas_v=[Areas_v Areas_opt];
		minmaxv=[minmaxv minmax_opt];

		//chama a funcao que faz o balanco das areas da casca convexa Com a
		//ordenação a partir do maior espaçamento, esta versao faz o
		//balanceamento apenas por dentro, sem cruzar a descontinuidade.
		[Areas,W,H,B] = balance_and_fix_oo4(n_wp, k, W, H, B, Areas);
		minmax=max(Areas)-min(Areas);

		it=1;
		while sum(Areas-Areas_opt) <> 0 & it <= 100

			if minmax < minmax_opt  then
				minmax_opt = minmax;
				W_opt=W;
				Areas_opt=Areas;
				H_opt=H;
				Areas_v=[Areas_v Areas_opt];
				minmaxv=[minmaxv minmax_opt];
				//encontra os gaps entre de cada class
		 	end
			[Areas,W,H,B] = balance_and_fix_oo4(n_wp, k, W, H, B, Areas);
			minmax=max(Areas)-min(Areas);
			it=it+1;
		end
	elseif k == 1
		indexes=[1 n_wp n_wp];
		wp_full = [ones(n_wp,1) wp];

		//se so tiver uma classe, apenas faz com que o ang(1) seja 0
		min_wp_rho=min(wp_full(:,4));
		wp_full(:,4) = wp_full(:,4) - min_wp_rho*ones(n_wp,1);
     
		W(k).coord=[[0 0 0 0]; wp_full(indexes(k,1):indexes(k,2),2:5)];
		W(k).n=indexes(k,3)+1;
		[nH, indH,not_indH]=myconvex_hull(W(k).coord(:,1:3));
		[idx idx_pos]=min(indH);
		indH = [indH(idx_pos:nH), indH(1:idx_pos-1) ];

		H(k).idxW=indH;
		H(k).n=nH;
		B(k).idxW=not_indH;
		B(k).n=W(k).n-nH;

		W_opt=W;
		H_opt=H;
		[Area1, Area2]=area_calc(W(k).coord(idxH,1),W(k).coord(indH,2),W(k).coord(:,4),indH);
		Areas_opt=Area1;
	else
    	disp('Erro: número de VANTs inválido');
	end

	plota_wpoo(W_opt, H_opt,k);
