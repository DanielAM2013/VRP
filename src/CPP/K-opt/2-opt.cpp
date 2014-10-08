#include "k-opt.hpp"

int main(){
 
 char f[]="points.dat";
 route R=read_route(f);

// print_route(R);
// Dado um arquivo com uma lista de pontos
// devemos remover os possiveis cruzamentos nesta rota

 opt2(&R);
// print_route(R);

 char o[]="route.dat";
 save_route(&R,o);

 return 0;
}
