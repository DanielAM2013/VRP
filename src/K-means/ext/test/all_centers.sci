function all_center = all_centers( cluster)

	k=size(cluster,1);

	all_center=cell(k,1);
	for i=1:k
		all_center(i).entries=centers(cluster,i);
	end

endfunction
