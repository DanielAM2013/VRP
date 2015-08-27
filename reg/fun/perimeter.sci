function	val=perimeter(points)

	n=size(points,1);

	val=0;
	for i=1:n-1
		val=val+norm(points(i+1,:)-points(i,:));
	end
	val=val+norm(points(1,:)-points(n,:));

endfunction
