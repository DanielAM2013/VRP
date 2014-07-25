#include "tsp.h"

int main()
{
 ponto *P, *Aux[4];
 double perc=0;
 int i;
 char s[10]="dados.txt";

 P=read_file_points(s);

 ponto* route=NULL;

 cout << create_route(&route, &P) << endl;

 char saida[10]="saida.txt";
 salve_file(route,saida);

 Aux[0]=route;
 do {
  Aux[1]=Aux[0]->next;
  delete Aux[0];
  Aux[0]=Aux[1];

 } while(Aux[0]!=route);

 return 0;
}
