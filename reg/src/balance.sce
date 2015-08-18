clear
clf


exec ../fun/balance_and_fix_oo3.sci;
exec ../fun/area_calc.sci
exec ../fun/kmeans.sci
exec ../fun/pi22pi.sci
exec ../fun/myconvex_hull.sci
exec ../fun/myconvex_hull_rem.sci
exec ../fun/plota_wpoo.sci
//exec myconvex_fix_add.sci //refaz a casca convexa a partir da entrada de um ponto com angulo extremo aos existentes

	// data:= conjunto de pontos no plano
	data=read('../dat/input.dat',-1,2);

	deg=%pi/180;

	// Oidx:= indice da origem em data
	Oidx=10;

	// O:= origem de data
	O=data(Oidx,:);

	data(Oidx,:)=[];

	// k:= número de classes a dividir data
	k=4;

	condiciona=1;

	// n:= número de pontos em data sem a origem
	n=size(data,1)

	// wp:= data deslocado de O
	wp=data-ones(n,1)*O;

	// Reescala para que as normas sejam maiores que a unidade
	for i=1:n
		norm_wp(i)=norm(wp(i,1:2),2);
	end
	min_norm=min(norm_wp);
	wp=wp/min_norm;
	points=wp;

	// calcula o angulo rho sempre entre 0 e 360 em graus
	wp_rho = pi22pi(atan(wp(:,2), wp(:,1)))/deg;

	// calcula a distancia ate o ponto a partir do lancamento
	wp_dist = norm_wp/min_norm;

	//aplica uma rotacao para que o minimo angulo seja zero.  com isso o maior
	//angulo é menor que 360, colocando a descontinuidade em um gap.  esta
	//operacao tem que ser repetida sempre que houver uma troca de classe do
	//angulo 0, que deve ser sempre a classe um (por convencao)
	// min_rho=min(wp_rho)
	// wp_rho = wp_rho - min_rho*ones(wp_rho)

	wp = [wp wp_rho wp_dist];

	//ordena wp_full a partir do angulo menor para o maior que deve ser sempre
	//menor ou igual a 360. Isso forca que as classes estejam agrupadas

	[counter_clock,ord_rho]=gsort(wp(:,3),'g','i');
	wp=wp(ord_rho,:);

	//melhor condiciona os pontos fazendo duas coisas: agrupando os angulos
	//muito proximos em apenas um, sendo que o angulo resultante o relacionado
	//com o mais distante, mantendo os dois pontos. Caso a diferenca de
	//distancia esteja dentro da cobertura da camera, entao o ponto resultante
	//um novo ponto que é a media de todos. Um novo angulo é entao calculado.

	wp = [wp [1:n]'];
	wp_original = wp;

	// operador merge: faz o merge entre dois pontos proximos. Esta operacao
	// substitui dois pontos de passagem pela media deles. A distancia afast_max
	// é a metade ma menor distancia da projetcao de uma camera no solo.
	afast_max = 3;

	if condiciona == 1 
		i=1
		tsp=[]
		while i<=n-1
		j=i+1
    while j<=n
          afast= sqrt((wp(i,1)-wp(j,1))^2 + (wp(i,2)-wp(j,2))^2)
          diff_ang = abs(wp(i,3)-wp(i+1,3)),
          [deeper, idx] = max(wp(i,4),wp(i+1,4));
          projec = sin(diff_ang*deg)*deeper
        if afast < afast_max
            wp(i,1)=(wp(i,1)+wp(j,1))/2;
            wp(i,2)=(wp(i,2)+wp(j,2))/2;
            wp_rho = atan(wp(i,2), wp(i,1));
            wp(i,3)=pi22pi(wp_rho)/deg
            wp(i,4) = sqrt(wp(i,1)^2 + wp(i,2)^2)
            wp(j,:)=[];
            n=n-1
            break
// operador eclipse, sempre que a projecao de um ponto passar pela visinhanca
// de algum outro com distancia maior, o de distancia maior será usado e o
// de distancia menor é guardado para o TSP.
          elseif projec < afast_max/4
              tsp=[tsp; wp(i-idx+2,:) i];
              wp(i-idx+2,:)=[]
              n=n-1
           else
              j=j+1
          end
        end
        i=i+1
end


//ordena wp de novo depois da operacao de condicionamento

[counter_clock,ord_rho]=gsort(wp(:,3),'g','i');
wp=wp(ord_rho,:);

end


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
  
  wp_ord=zeros(n,6);
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
     min_rho=min(wp_ord(:,4))
     wp_ord(:,4) = wp_ord(:,4) - min_rho*ones(n,1)
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
//return

[Areas,W,H,B] = balance_and_fix_oo3(n, k, W, H, B, Areas);
minmax=max(Areas)-min(Areas)

clf

plota_wpoo(W, H,k)


it=1

while sum(Areas-Areas_opt) <> 0 & it <= 50

   if minmax < minmax_opt  then
     clf
     minmax_opt = minmax;
     W_opt=W
     Areas_opt=Areas  
     H_opt=H
     Areas_v=[Areas_v Areas_opt]
     minmaxv=[minmaxv minmax_opt]
     plota_wpoo(W_opt, H_opt,k)
     
       //encontra os gaps entre de cada classe
      gaps = zeros(k,1)
      gaps(1)=360+(W(1).coord(2,3)-W(k).coord(W(k).n,3))
      for i=1:k-1
          gaps(i+1)=W(i+1).coord(2,3)-W(i).coord(W(i).n,3)
      end

     
   end
   [Areas,W,H,B] = balance_and_fix_oo3(n, k, W, H, B, Areas);
      minmax=max(Areas)-min(Areas)
   it=it+1

end
elseif k == 1
    indexes=[1 n n]
     wp_full = [ones(n,1) wp];
     //se so tiver uma classe, apenas faz com que o ang(1) seja 0
     min_rho=min(wp_full(:,4))
     wp_full(:,4) = wp_full(:,4) - min_rho*ones(n,1)
     
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




