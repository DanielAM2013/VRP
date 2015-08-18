//Melhor condiciona os pontos fazendo duas coisas: agrupando os angulos
//muito proximos em apenas um, sendo que o angulo resultante o relacionado
//com o mais distante, mantendo os dois pontos. Caso a diferenca de distancia
//esteja dentro da cobertura da camera, entao o ponto resultante um novo ponto
//que é a media de todos. Um novo angulo é entao calculado.
function [wp, n_wp]=wp_cond(wp, n_wp, afast_max)

    i=1
    tsp=[]
    while i<=n_wp-1
        j=i+1
        while j<=n_wp
			//afast=norm(wp(i,1:2)-wp(j,1:2),2);
			afast= sqrt((wp(i,1)-wp(j,1))^2 + (wp(i,2)-wp(j,2))^2)
			diff_ang = abs(wp(i,3)-wp(i+1,3)),
			[deeper, idx] = max(wp(i,4),wp(i+1,4));
			projec = sin(diff_ang*deg)*deeper
			// operador merge: faz o merge entre dois pontos proximos. Esta
			// operacao substitui dois pontos de passagem pela media deles. A
			// distancia afast_max é a metade ma menor distancia da projetcao de
			// uma camera no solo.
			if afast < afast_max
				wp(i,1)=(wp(i,1)+wp(j,1))/2;
				wp(i,2)=(wp(i,2)+wp(j,2))/2;
				wp_rho = atan(wp(i,2), wp(i,1));
				wp(i,3)=pi22pi(wp_rho)/deg
				wp(i,4) = sqrt(wp(i,1)^2 + wp(i,2)^2)
				wp(j,:)=[];
				n_wp=n_wp-1
				break
				// operador eclipse, sempre que a projecao de um ponto passar
				// pela visinhanca de algum outro com distancia maior, o de
				// distancia maior será usado e o de distancia menor é guardado
				// para o TSP.
			elseif projec < afast_max/4
				tsp=[tsp; wp(i-idx+2,:) i];
				wp(i-idx+2,:)=[]
				n_wp=n_wp-1
			else
				j=j+1
			end
		end
		i=i+1
	end
	//ordena wp de novo depois da operacao de condicionamento
	[counter_clock,ord_rho]=gsort(wp(:,3),'g','i');
	wp=wp(ord_rho,:);
endfunction
