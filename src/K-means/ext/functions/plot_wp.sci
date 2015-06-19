function plota_wp(wp_full,k)
    
    classes=wp_full(:,1);
    wp=wp_full(:,2:3);

	membership=[];
	elementos =[];
	for i=1:k

		membership = (classes == i);
		elementos = wp(membership, :);

     	plot(elementos(:,1),elementos(:,2),'xr');

		elementos = [[0,0]; elementos];
     	[nhull1, ind1]=convex_hull(elementos');
	 	elementos=elementos(ind1,:);
		elementos=[elementos; elementos(1,:)];

		plot(elementos(:,1), elementos(:,2) ,'r');
   		last_line=gce();
		last_line.children.line_mode="on";
		last_line.children.foreground=i+1;
		last_line.children.thickness=2;

	end
endfunction

