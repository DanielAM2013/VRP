function centerd = centers( cluster, i)

	k=size(cluster,1);

	if i>k | i<0
		return;
	end


	m=size(cluster(i).entries,1)
	centerd=[sum(cluster(i).entries(:,1)), sum(cluster(i).entries(:,2))]/m;

endfunction
