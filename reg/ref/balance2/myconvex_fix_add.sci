//function [idxH,not_idxH]=myconvex_hull(Pt)
function [H_out, B_out]=myconvex_fix_add(Wnew, H_old, B_old, idx_new)

if idx_new == 2
     B_out=B_old
     B_out.idxW= B_out.idxW+1
     H_out.idxW=[1 H_old.idxW+1]
     H_out.n=H_old.n+1
     points=Wnew.coord(H_out.idxW,:)

     first = points(2,1:2)
     second = points(3,1:2)
     third = points(4,1:2)
     cross_prod = ccw(first, second, third)
     not_idxH_part=[]
                  
     while cross_prod < 0 & length(H_out.idxW) > 2
//           if B_out.idxW(B_out.n) > H_out.idxW(H_out.n-1)
               posB = find(B_out.idxW > H_out.idxW(3),1)
               B_out.idxW=[B_out.idxW(1:posB-1) H_out.idxW(3) B_out.idxW(posB:B_out.n)]
//           else
 //              B_out.idxW=[B_out.idxW H_out.idxW(H_out.n-1)]
 //          end
           B_out.n=B_out.n+1
           points(3,:)=[]
           H_out.idxW(3)=[]
           H_out.n=H_out.n-1
           second=third
           third = points(4,1:2)
          // Find next valid point on convex hull.
         cross_prod = ccw(first, second, third)
     end
     
elseif idx_new==Wnew.n
     B_out=B_old
     H_out.idxW=[H_old.idxW Wnew.n]
     H_out.n=H_old.n+1
     points=Wnew.coord(H_out.idxW,:)

     first = points(H_out.n,1:2)
     second = points(H_out.n-1,1:2)
     third = points(H_out.n-2,1:2)
     cross_prod = ccw(first, second, third)
     not_idxH_part=[]
                  
     while cross_prod > 0 & length(H_out.idxW) > 2
           if B_out.idxW(B_out.n) > H_out.idxW(H_out.n-1)
               posB = find(B_out.idxW > H_out.idxW(H_out.n-1),1)
               B_out.idxW=[B_out.idxW(1:posB-1) H_out.idxW(H_out.n-1) B_out.idxW(posB:B_out.n)]
           else
               B_out.idxW=[B_out.idxW H_out.idxW(H_out.n-1)]
           end
           B_out.n=B_out.n+1
           points(H_out.n-1,:)=[]
           H_out.idxW(H_out.n-1)=[]
           H_out.n=H_out.n-1
           second=third
           third = points(H_out.n-2,1:2)
          // Find next valid point on convex hull.
         cross_prod = ccw(first, second, third)
     end
 end

endfunction

function [cross_prod]=ccw(p1, p2, p3)
    cross_prod = (p2(1) - p1(1))*(p3(2) - p1(2)) - (p2(2) - p1(2))*(p3(1) - p1(1))
endfunction
