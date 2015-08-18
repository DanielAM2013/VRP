function plotd(cluster,i)
    
	elementos = cluster(i).entries;
	
   	plot(elementos(:,1),elementos(:,2),'ob');

//	elementos = [[0,0]; elementos];
   	[trash, idx]=convex_hull(elementos');
 	elementos=elementos(idx,:);
	elementos=[elementos; elementos(1,:)];

	plot(elementos(:,1), elementos(:,2) ,'r');
	last_line=gce();
	last_line.children.line_mode="on";
	last_line.children.foreground=i+1;
	last_line.children.thickness=2;

endfunction

