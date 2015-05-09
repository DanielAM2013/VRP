#include <k-opt.hpp>

int main( int argv, char* argc[]){
 
 route R=read_route(argc[1]);

// Dado um arquivo com uma lista de pontos
// devemos remover os possiveis cruzamentos nesta rota
 for( int k=0; k<10; k++)
  opt2(&R);

 save_route(&R,argc[2]);

 return 0;
}
