function [output, area]=heuristica2(cluster, origin)

	k=size(cluster,1);

	area=zeros(k,1);

	for i=1:k
		Aux=[cluster(i).entries; [0, 0]];
		[trash, idx]=convex_hull(Aux');
		area(i)=area_calc(Aux(idx,:));
	end

	[trash, idx_max]=max(area);
	output=cluster;
	if idx_max > 1 & idx_max < k
		lim_inf=idx_max-1;
		lim_sup=idx_max+1;
	elseif idx_max==1
		lim_inf=k;
		lim_sup=idx_max+1;
	elseif idx_max==k
		lim_inf=idx_max-1;
		lim_sup=1;
	end

	Aux=cluster(idx_max).entries;
	m=size(Aux,1);
	Test=dist(Aux(m,:),Aux(m-1,:)) > dist(Aux(2,:),Aux(1,:));

	if	Test
		pos=m
		class=lim_sup;
	else
		pos=1
		class=lim_inf;
	end

	output(idx_max).entries(pos,:)=[];
	output(class).entries=[output(class).entries; Aux(pos,:)];

endfunction
