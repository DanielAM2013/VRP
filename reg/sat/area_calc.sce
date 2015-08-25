// File create to test area_calc.sci 

clear;

points=read('dat/input.dat',-1,2);

exec fun/area02.sci;

	disp('=area',area02(points));

exec fun/area_calc.sci;

	n=size(points,1);
	for i=1:n-1
		dists(i)=norm(points(i+1,:)-points(i,:));
	end
	dists(n)=norm(points(n,:)-points(1,:));

	indi=1:n;

	[area1,area2]=area_calc(points(:,1),points(:,2),dists,indi);

	disp('=area1',area1,'=area2',area2);
