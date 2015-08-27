clear;
clf;
	i=1;
	points=read('dat/input.dat',-1,2);

	n=size(points,1);

	[nhull, ind]=convex_hull(points(1:n,:)');
	if nhull==0
		nhull=n;
		ind=1:n;
	end
	cvx(i).nhull=nhull;
	cvx(i).ind=ind;

	// Calculate inner points
	idx=gsort(ind,'g','i');
	ind_not=1:idx(1)-1;
	for j=1:nhull-1
		ind_not=[ ind_not idx(j)+1:idx(j+1)-1];
	end
	cvx(i).ind_not=ind_not;

	set_plot=[ points(cvx(i).ind,:); points(cvx(i).ind(1),:)];
//	plot(set_plot(:,1),set_plot(:,2));

	N=size(ind_not,2);

	while N>1

		i=i+1;
		// Calcula o convexo do conjunto interior anterior
		[nhull, ind]=convex_hull(points(ind_not,:)');
		if nhull==0
			nhull=N;
			ind=1:N;
		end
		cvx(i).nhull=nhull;
		cvx(i).ind=ind_not(ind);

		// Calcula o novo conjunto interior
		ind_not=[];
		for j=1:N
			s=0;
			for k=1:nhull
				if cvx(i).ind(k)==cvx(i-1).ind_not(j)
					s=s+1;
				end
			end
			if s==0
				ind_not=[ ind_not cvx(i-1).ind_not(j)];
			end
		end
		N=size(ind_not,2);

		cvx(i).ind_not=ind_not;

		// Plot
		set_plot=[ points(cvx(i).ind,:) ; points(cvx(i).ind(1),:)];
//		plot(set_plot(:,1),set_plot(:,2));

	end

	exec fun/insert.sci;
	exec fun/convex_merger.sci;
	exec fun/perimeter.sci;

	n=size(cvx,1);
	idx=cvx(1).ind;
	for i=2:n
		idx=convex_merger(points,idx,cvx(i).ind);
	end

	clf;
	for i=1:n
		idx_plot=[cvx(i).ind cvx(i).ind(1)];
		plot(points(idx_plot,1),points(idx_plot,2));
	end

	disp(perimeter(points(idx,:)));
	set_plot=[points(idx,:); points(idx(1),:)];
	plot(set_plot(:,1),set_plot(:,2),'rx-');

	xs2png(0,'fig/cvx1.png');

	idx=cvx(n).ind;
	for i=n-1:-1:1
		idx=convex_merger(points,cvx(i).ind,idx);
	end

	clf;
	for i=1:n
		idx_plot=[cvx(i).ind cvx(i).ind(1)];
		plot(points(idx_plot,1),points(idx_plot,2));
	end
	disp(perimeter(points(idx,:)));
	set_plot=[points(idx,:); points(idx(1),:)];
	plot(set_plot(:,1),set_plot(:,2),'rx-');
	xs2png(0,'fig/cvx2.png');
