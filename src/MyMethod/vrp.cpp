#include "vrp.hpp"
#include <sstream>

route read_file(char file[]) {

 std::ifstream data(file, std::ifstream::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 route *aux=new route;
 aux->subroute=*R;
 
 // Enviar um veículo para cada ponto
 for( ponto *i=R->next; i!=NULL; i=i->next) {
  aux=aux->next=new route;
  aux->subroute=*i;
 }


void print_train(train T) 
{
 std::cout << "---------------------------------------" << std::endl;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
}

void save_train( train T) {
 unsigned int k=0;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  std::stringstream s;
  s << k << ".test";
  std::ofstream  out(s.str().c_str());

  for( route::iterator j=i->begin(); j!=i->end(); j++)
   out << j->real() << " " << j->imag() << std::endl;
  out.close();
  k++;
 }
}


int main()
{
// Ler Arquivo
 char test[]="points.dat";
 route first=read_file(test); 

 int N=first.size();

/*
 for( route::iterator i=first.begin(); i!=first.end(); i++)
  std::cout << *i << std::endl;

 std::cout << tsp(&first) << std::endl;

 for( route::iterator i=first.begin(); i!=first.end(); i++)
  std::cout << *i << std::endl;
*/
 point aux=*first.begin();

 for( route::iterator i=first.begin(); i!=first.end(); i++) {
  *i-=aux;
 }
// Ordenar
 std::sort(first.begin()+1, first.end(), operator<);

 for( route::iterator i=first.begin(); i!=first.end(); i++) {
  *i+=aux;
 }

// Alocar
 train second;
 for( int i=1; i<N; i++) {
  route aux;
  aux.push_back(first[0]);
  aux.push_back(first[i]);
  second.push_back(aux);
  aux.clear();
 }

 double d[3]={0,0,cust(second)};

 train Aux, Aux1(second);

 for( int k=0; k<N; k++)
// while(d[1]<d[2])
 {
  d[2]=d[1];
  Aux=train(second);
  second=train(Aux1);
  d[1]=cust(Aux);
  for( train::iterator i=Aux.begin(); i+1!=Aux.end(); i++) {
   // Mesclar roca com a seguinte numa variável auxiliar
   i->insert(i->end(), (i+1)->begin()+1, (i+1)->end());
   // Aplicar o tsp
   tsp(&*i);
   // Inserir rotas mescladas no train Aux
   Aux.erase(i+1);
   // Avaliar roteamento
   d[0]=cust(Aux);
   // Ordenar custo
   if(d[0]<d[1]) {
    d[1]=d[0];
    Aux1=train(Aux);
   }
//   print_train(Aux);
   Aux=train(second);
  }

  Aux=train(second);
  
  (Aux.end()-1)->insert((Aux.end()-1)->end(), (Aux.begin())->begin(), (Aux.begin())->end());

  tsp(&*(Aux.end()-1));
  // Inserir rotas mescladas no train Aux
  Aux.erase(Aux.begin());
  // Avaliar roteamento
  d[0]=cust(Aux);
 // Ordenar custo
  if(d[0]<d[1]) {
   d[1]=d[0];
   Aux1=train(Aux);
  }
//  print_train(second);
 }
 save_train(second);
 std::cout << cust(second) << std::endl;

 return 0;
}
