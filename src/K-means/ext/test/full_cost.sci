function [value, pcenter] = full_cost (cluster)

	k=size(cluster,1);

	value=0;
	pcenter=cell(k,1);
	for i=1:k
		[inc, pcenter(i).entries]=cost(cluster,i);
		value=value+inc;
	end

endfunction
