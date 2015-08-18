function plotd_all( cluster, pcenter, origin)

	k=size(cluster,1);

	Aux=cluster;
	for i=1:k
		m=size(Aux(i).entries,1);
		Aux(i).entries=Aux(i).entries+ones(m,1)*origin;
		Aux(i).entries=[Aux(i).entries; origin];
		plotd(Aux,i);
		aux=pcenter(i);
		aux.entries=aux.entries+origin;
		plot(aux.entries(1),aux.entries(2),'x');
	end

endfunction
