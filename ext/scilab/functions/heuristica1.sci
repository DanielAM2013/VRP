function [wp_new, wp_ord, nv]=balance(all, k)

	n=size(all,1);
	wp=all(:,2:3);

	//ordena as classes
	wp_ord = [];

	// Separa os pontos em partes do vetor wp_ord
	nv=[];
	for i=1:k
    	ni=0;
	    for j=1:n
    		if all(j,1) == i;
        		wp_ord = [wp_ord; all(j,:)];
        		ni=ni+1;
     		end
    	end
    	nv=[nv;ni];
	end

	//separa as classes
	aberturav=[];
	minimus = [];
	maximus = [];
	area_sections = [];

	for i=1:k
		// marca a posição inicial de uma classe em wp_ord
    	class_init = sum(nv(1:i-1));
		// marca a posição final de uma classe em wp_ord
    	class_fim = class_init + nv(i);

		// obtem apenas determinada classe de all
    	wpi=wp_ord(class_init+1:class_fim, :);

		// determina o ponto com menor angulo da classe
     	[trash, idx_min] = min(wpi(:,4));

		// determina o ponto com menor angulo da classe
    	[trash, idx_max] = max(wpi(:,4));

		// Seleciona apenas os pontos com menor angulo em cada classe
    	minimus = [minimus;[wpi(idx_min,:),idx_min]];
		// Seleciona apenas os pontos com maior angulo em cada classe
   		maximus = [maximus;[wpi(idx_max,:),idx_max]];

		// wpi adicionado da origem
   		wpi0=[wpi(:,2:3);[0 0]];

		// provavelmente uma função que calcula o convexo de wpi0
   		[trash, indi]=convex_hull(wpi0');

   		area_sections = [area_sections; area_calc(wpi0(indi,:))];
	end

	//ordena os setores para sempre contarem crescente no sentido anti-horario
	limitsPI=[minimus(:,4) maximus(:,4)];
	limitsDEG=pi22pi(limitsPI)/deg;

	// Ordena os limites dos convexos
	[trash, ord_sec]=gsort(limitsDEG(:,1),'g','i');
	//limits_ord = limitsDEG(ord_sec,:);
  
	area_sorted=[[1:k]' area_sections];
	area_sorted=area_sorted(ord_sec,:);

	//encontra a classe de maior area e sua posicao na ordem das secoes no sentido anti horario
	[trash, position]=max(area_sorted(:,2));

	// maior area das seções
	chass=area_sorted(position,1);

	// encontra o vizinho com menor area e desloca o ponto mais proximo para ele
	if position > 1 & position < k
		[trash, index] = min(area_sorted(position-1,2),area_sorted(position+1,2));
		if index == 1
			changing=area_sorted(position-1,:);
			swop=minimus(chass,5);
		else
			changing=area_sorted(position+1,:);
			swop=maximus(chass,5);
		end
	else
		disp('test');
			[trash, index] = min(area_sorted(1,2),area_sorted(k,2));
		if index == 1
			changing=area_sorted(1,:);
			swop=maximus(chass,5);
		else
			changing=area_sorted(k,:);
			swop=minimus(chass,5);
		end
	end

	class_changing_area=changing(1);

	all(swop,1)=class_changing_area;

endfunction
