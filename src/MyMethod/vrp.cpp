#include <iostream>
#include <fstream>
#include <new>
#include <complex>
//using namespace std;

/*
Alg:

 *) Rotas iniciais 
 **) Varredura de rotas;
 ***) Mesclagem de rotas;

*/

/*
double route_cust(route R);
double subroute_cust(subroute r);
void read_file(char a[]);
*/


/*
Estrutura:

 As rotas devem ser representadas por listas circulares duplamente encadeadas.
 Assim como a conboio.

*/

class rota 
{
 private:
  std::complex<double> coord;
  rota* next;
  rota* prev;
 public:
  rota(double x=0, double y=0) {
   coord.real()=x;
   coord.imag()=y;
  }

  void display(void) {
   rota* aux=this;
   while(aux) {
   }
  }

};


int main()
{
 char a[]="daniel";

// Para todas os pares de rotas calcular custo do roteamento
 rota(1.2,1.2);






 return 0;
}
