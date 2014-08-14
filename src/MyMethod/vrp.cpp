#include "tsp.h"

double vrp(ponto *R) {

 double d[2]={1e+30,0};

 route *aux=new route;
 aux->subroute=*R;
 
 // Enviar um veículo para cada ponto
 for( ponto *i=R->next; i!=NULL; i=i->next) {
  aux=aux->next=new route;
  aux->subroute=*i;
 }




 // Ordenar os pontos por ângulo e módulo
 // Calcular o custo para esta situação

// while(std::abs(d[1]-d[0])>1e-2) {
//  for( ponto *i=R; i->next!=NULL; i=i->next) {
   // copiar R para aux
   // mesclar rodas adjacentes
   // Calcular custo
   // Avaliar ordem do resultado e quardar poteiro para o primeiro elemento do par
//  }
  // Copiar aux para R
// }

 return d[1];
}


int main()
{




	
 return 0;
}
