clear;

exec fun/objCost.sci;
exec fun/kmeans.sci;

	data=read('dat/input.dat',-1,2);

	Oidx=10;

	O=data(10,:);

	data(Oidx,:)=[];


	k=5;
	deg=180/%pi;
	rho=modulo(2*%pi+atan(data(:,2)-O(2),data(:,1)-O(1)),2*%pi);
	[classes, centers, sumd, D, err]=kmeans(rho, k);

	clf
	for i=1:k

		points = data(classes==i, :);

     	plot(points(:,1),points(:,2),'xr');

		points=[ O; points];
     	[trash, ind1]=convex_hull(points');
		if trash==0
			points=[points; O];
		else
		 	points=points(ind1,:);
			points=[points; points(1,:)];
		end

		plot(points(:,1), points(:,2) ,'r');
   		last_line=gce();
		last_line.children.line_mode="on";
		last_line.children.foreground=i+1;
		last_line.children.thickness=2;

	end
