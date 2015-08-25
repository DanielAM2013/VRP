clear;

points=read('dat/input.dat',-1,2);


exec fun/ccw.sci;
exec fun/myconvex_hull.sci;
//exec fun/myconvex_fix_add.sci;
exec fun/convex_add.sci;

	[nidxW, H.idxW, B.idxW]=myconvex_hull(points);

	H.n=length(H.idxW);
	B.n=length(B.idxW);
	W.coord=points;
	W.n=size(points,1);

	point=points(1,1:2)+0.1;

	idx_new=2;
	[Ho, Bo]=convex_add(W,H,B,point);

//	plot(points(Bo.idxW,1),points(Bo.idxW,2),'x');
//	plot(point(1),point(2),'xr');
//	plot(points(1,1),points(1,2),'xr');

	plot(points(H.idxW,1),points(H.idxW,2));
	plot(points(B.idxW,1),points(B.idxW,2),'xr');




	
