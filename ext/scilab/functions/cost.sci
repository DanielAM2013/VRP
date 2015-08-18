function [value, pcenter] = cost (cluster, i)

	k=size(cluster,1);

	if i > k & i < 0
		return;
	end

	pcenter=centers(cluster,i);

	m=size(cluster(i).entries,1);

	value=0;
	for j=1:m
		value=value+dist(cluster(i).entries(j,:),pcenter)^2;
	end

endfunction
