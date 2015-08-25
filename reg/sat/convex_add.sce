clear;

points=read('dat/input.dat',-1,2);


exec fun/ccw.sci;
exec fun/myconvex_hull.sci;
//exec fun/myconvex_fix_add.sci;
exec fun/convex_add.sci;

	n=size(points,1);

	if n>1
	[H.n, H.idxW]=convex_hull(points');

	for i=1:n

	end
	B.n=n-H.n;
	

	W.coord=points
	
	idx_new=2;
//	[Ho, Bo]=convex_add(points,H,B,idx_new);
	

