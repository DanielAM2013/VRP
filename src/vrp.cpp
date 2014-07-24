#include "tsp.h"
// basic code

typedef struct Rota {

 complex<double> coord;
 struct Source* next;
 struct ponto* sub;

} rota;

double diff_arg(complex<double> p, complex<double> q, complex<double> ref)
{
 return (arg(p-ref)-arg(q-ref));
}


void ins_sort(rota* P, complex<double> p)
{
 rota* Aux[2];
 double delta;

 Aux[0]=P;

 while(Aux[0]) {

  delta=diff_arg(Aux[0]->coord, p, P->coord)*diff_arg(Aux[0]->next->coord, p, P->coord);

  if(delta < 0);
  else
  if(delta = 0);
  else
  Aux[0]=Aux[0]->next;
 }

}

/*
void sort_points(ponto* P)
{
 ponto* Aux[2];
 complex<double> aux[2];

 ponto* AUX[2];

 AUX[0]=new ponto;

 Aux[0]=P;
 AUX[0]->coord=Aux[0]->coord;

 while(Aux[0]) {
  Aux[1]=Aux[0]->next; 
  while(Aux[1]) {
    aux[0]=Aux[1]->coord-P->coord;
    if(aux[0].arg()<0) {
     AUX[1]=new ponto;
     AUX[0]
    }
   Aux[1]=Aux[1]->next;
  }
  Aux[0]=Aux[0]->next;
 }

}
*/

int main()
{
 // Ordenar por ângulo

 // dado um conjunto de pontos em uma estrutura osdena-los em relação ao ângulo ao primeiro ponto





 return 0;
}
