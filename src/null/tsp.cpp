#include "tsp.h"

int main()
{
 char in[]="dados.txt", out[]="saida.txt";
 ponto *P=read_file_points(in), Aux[2];

/*
 ponto* route=NULL;

 cout << create_route(&route, &P) << endl;

 salve_file(route,saida);

 Aux[0]=route;
 do {
  Aux[1]=Aux[0]->next;
  delete Aux[0];
  Aux[0]=Aux[1];

 } while(Aux[0]!=route);
*/

 cout << tsp(P) << endl; 
 salve_file(P,out);
/*
 Aux[0]=P;
 while(Aux[0]!=NULL) {
  Aux[1]=Aux[0]->next;
  delete Aux[0];
  Aux[0]=Aux[1];
 }
*/
 return 0;
}
