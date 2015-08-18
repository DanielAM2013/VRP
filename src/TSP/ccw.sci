function [cross_prod]=ccw(p1, p2, p3)
    cross_prod = (p2(1) - p1(1))*(p3(2) - p1(2)) - (p2(2) - p1(2))*(p3(1) - p1(1))
endfunction
