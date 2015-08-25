clear

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

//! Aquisição de pontos

	// data:= conjunto de pontos no plano
	data=read('dat/input.dat',-1,2);

	deg=%pi/180;

	// Oidx:= indice da origem em data
	Oidx=10;
//	Oidx=input('value Oidx:= ');

	// k:= número de classes a dividir data
	k=4;
//	k=input('value k:= ');

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
	if k > 0  then
		//chama a função kmeans
		[classes, centers, sumd, D, err] = kmeans(wp(:,3), k);

		// Encontra os indices minimos e maximos de cada classe

		// indexes:=[ indice mínimo indice máximo intervalo] da classe
		indexes=zeros(k,3);
		gaps = zeros(k,1);
		indexes(1,1)=min(find(classes==1));
		indexes(k,2)=max(find(classes==k));
		gaps(1)=360+(wp(indexes(1,1),3)-wp(indexes(k,2),3));
		for i=1:k-1
			indexes(i,2)=max(find(classes==i));
			indexes(i+1,1)=min(find(classes==i+1));
			gaps(i+1)=wp(indexes(i+1,1),3)-wp(indexes(i,2),3);
		end
		indexes(:,3)=indexes(:,2)-indexes(:,1)+1;

		// Ordena os indices minimos das classes
		[trash, ord_class]=gsort(indexes(:,1),'g','i');
		indexes=indexes(ord_class,:);

		// Ordena colocando o gap máximo no início

		// idxG:= índice do maior gap
		[trash, idxG]=max(gaps);

		// idxC:=indice das classes
		idxC=[idxG:k 1:idxG-1]';

		wp_ord=zeros(n,6);
		for i=1:k
			idxL=indexes(idxC(i),:);
			wp_ord(idxL(1):idxL(2),:)=[i*ones(idxL(3),1) [wp(idxL(1):idxL(2),:)]];
		end
 
		//aplica uma rotacao para que o minimo angulo seja zero.  com isso o
		//maior angulo é menor que 360, colocando a descontinuidade em um gap.
		//esta operacao tem que ser repetida sempre que houver uma troca de
		//classe do angulo 0, que deve ser sempre a classe um (por convencao)

		//As classes ja estao agrupadas. Faz agora usando as structs
		for i=1:k
			W(i).coord=[[0 0 0 0]; wp_ord(indexes(i,1):indexes(i,2),2:5)];
			W(i).n=indexes(i,3)+1;
		end

		//Calcula a casca convexa a suas areas das classes iniciais para poder
		//chamar a funcao que faz o balanceamento

		Areas_v=[];
		minmaxv=[];

		Areas = zeros(k,1);

		// Calcula a casca convexa para cada classe e a área ocupada por esta,
		// além de reordenar os 
		for i=1:k
			// H(i):= [ idxH n];
			// idxH:= indices dos pontos da classe i que pertencem a casca
			// convexa
            // n:= númerod  de pontos de idxH

			// B(i):= [ idxW n];
			// idxW:= indices dos pontos da classe i que não pertencem a casca
			// convexa
			// n:= númerod  de pontos de idxH

			[H(i).n, indH, B(i).idxW]=myconvex_hull(W(i).coord(:,1:2));

			//reordena para que o ponto de lançamento, ou o de menor angulo,
			//seja também o 1o ponto da casca convexa
			[trash idx_pos]=min(indH);
			indH = [indH(idx_pos:H(i).n), indH(1:idx_pos-1) ];

			H(i).idxW=indH;

			B(i).n=W(i).n-H(i).n;

			[Areas(i), trash]=area_calc(W(i).coord(indH,1),W(i).coord(indH,2),W(i).coord(:,4), indH);
		end
		minmax=max(Areas)-min(Areas);

		//plota_wpoo(W, H,k)

		minmax_opt = minmax;
		W_opt=W;
		H_opt=H;
		Areas_opt=Areas;

		Areas_v=[Areas_v Areas_opt];
		minmaxv=[minmaxv minmax_opt];

		//chama a funcao que faz o balanco das areas da casca convexa Com a
		//ordenação a partir do maior espaçamento, esta versao faz o
		//balanceamento apenas por dentro, sem cruzar a descontinuidade.

		[Areas, W, H, B] = balance_and_fix_oo4(n, k, W, H, B, Areas);
		minmax=max(Areas)-min(Areas);
		test=sum(Areas-Areas_opt);
		it=1;
		while test <> 0 & it <= 200

			// Atualiza minmax_opt, W_opt, Areas_opt 
			if minmax < minmax_opt  then
				minmax_opt = minmax;
				W_opt=W;
				Areas_opt=Areas;
				H_opt=H;
				Areas_v=[Areas_v Areas_opt];
				minmaxv=[minmaxv minmax_opt];
				//plota_wpoo(W_opt, H_opt,k)
			end

			[Areas,W,H,B] = balance_and_fix_oo4(n, k, W, H, B, Areas);
			minmax=max(Areas)-min(Areas);
			test=sum(Areas-Areas_opt);
			it=it+1;
		end
	elseif k == 1
		indexes=[1 n n];
		wp_full = [ones(n,1) wp];
		//se so tiver uma classe, apenas faz com que o ang(1) seja 0
		min_rho=min(wp_full(:,4));
		wp_full(:,4) = wp_full(:,4) - min_rho*ones(n,1);

		W(k).coord=[[0 0 0 0];wp_full(indexes(k,1):indexes(k,2),2:5)];
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
		[Area1, Area2]=area_calc(W(k).coord(indH,1),W(k).coord(indH,2),W(k).coord(:,4), indH);
		Areas_opt=Area1; 
	else
        disp('Erro: número de VANTs inválido');
		return;
	end
	plota_wpoo(W_opt, H_opt,k)
