//function [idxH,not_idxH]=myconvex_hull(Pt)
function [nidxH,idxH, not_idxH]=myconvex_hull(points)

n = size(points,1)

//ordena com respeito ao angulo (no inicio nao precisa)
//[counter_clock,ord_rho]=gsort(points(:,3),'g','i');
//points=points(ord_rho,:);

//[val,idx]=min(points(:,2))
//tmp=points(idx,:)
//points(idx,:)=[]
//points=[tmp;points]

// We want points[0] to be a sentinel point that will stop the loop.
//points=[points(n,:);points]
//n=n+1

// m will denote the number of points on the convex hull.
idxH=[1, 2]
not_idxH=[]
m=2

for i = 3:n
    // Find next valid point on convex hull.
    cross_prod = ccw(points(idxH(m-1),1:2), points(idxH(m),1:2), points(i,1:2))
    if cross_prod == 0
          idxH = [idxH i]//considera que se é colinear esta na hull
          m=m+1 
    elseif cross_prod > 0
          idxH = [idxH i]
          m=m+1 
    else
        not_idxH_part=[]
        while cross_prod < 0 & m > 2
              not_idxH_part=[idxH(m) not_idxH_part]
              idxH(m)=[]
              m=m-1
              cross_prod = ccw(points(idxH(m-1),1:2), points(idxH(m),1:2), points(i,1:2))        
        end
        not_idxH=[not_idxH not_idxH_part]
        idxH = [idxH i]
        m=m+1
     end
end

[not_idxH,ord]=gsort(not_idxH,'g','i');

nidxH=length(idxH)

endfunction

function [cross_prod]=ccw(p1, p2, p3)
    cross_prod = (p2(1) - p1(1))*(p3(2) - p1(2)) - (p2(2) - p1(2))*(p3(1) - p1(1))
endfunction
