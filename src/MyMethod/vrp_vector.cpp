#include "vrp.hpp"

route read_file(char file[]) {

 std::ifstream data(file, std::ifstream::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 return first;
}

double tsp(route *R) {

 double d[3];
 d[2]=0;


 route::iterator closer[2];
 std::complex<double> aux;

 route::iterator last=R->begin();
 while(last+1!=R->end()) 
 {

  d[1]=1e+30;
  for( route::iterator i=last+1; i!=R->end(); i++) {
   for( route::iterator j=R->begin(); j!=last; j++) {
    d[0]=std::abs(*j-*i)+std::abs(*i-*(j+1))-std::abs(*j-*(j+1));
    
    if(d[0]<d[1]) {
     d[1]=d[0];
     closer[0]=i;
     closer[1]=j;
    }
   }
   d[0]=std::abs(*last-*i)+std::abs(*i-*R->begin())-std::abs(*last-*R->begin());

   if(d[0]<d[1]) {
    d[1]=d[0];
    closer[0]=i;
    closer[1]=last;
   }
  }
  aux=*closer[0];

  d[2]+=d[1];

  R->erase(closer[0]);

  R->insert(closer[1]+1, aux); 
  last++;
 }
 return d[2];
}

int main()
{
// Ler Arquivo
 char test[]="points.dat";
 route first=read_file(test); 

 int N=first.size();

// Ordenar
 std::sort(first.begin()+1, first.end(), operator<);
// Alocar
 train second;
 for( int i=1; i<N; i++) {
  route aux;
  aux.push_back(first[0]);
  aux.push_back(first[i]);
  second.push_back(aux);
  aux.clear();
 }

 for( train::iterator i=second.begin(); i!=second.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
 std::cout << cust(second) << std::endl;

 double d[3]={0,0,cust(second)};
 
 for( int k=0; k<N-2; k++) {

  train Aux(second), Aux1;
  route aux;

  d[1]=cust(Aux);
  for( train::iterator i=Aux.begin(); i+1!=Aux.end(); i++) {
   // Mesclar roca com a seguinte numa variável auxiliar
   aux=route(*i);
   aux.insert(aux.end(), (i+1)->begin()+1, (i+1)->end());
   // Aplicar o tsp
   tsp(&aux);
   // Inserir rotas mescladas no train Aux
   Aux.erase(i+1);
   *i=aux;
   // Avaliar roteamento
   d[0]=cust(Aux);
   // Ordenar custo
   if(d[0]<d[1]) {
    d[1]=d[0];
    Aux1=train(Aux);
   }
   Aux=train(second);
  }

  aux=route(*(second.end()-1));
  aux.insert(aux.end(), (second.begin())->begin(), (second.begin())->end());

  tsp(&aux);
  // Inserir rotas mescladas no train Aux
  Aux.erase(Aux.begin());
  *(Aux.end()-1)=aux;
  // Avaliar roteamento
  d[0]=cust(Aux);
 // Ordenar custo
  if(d[0]<d[1]) {
   d[1]=d[0];
   Aux1=train(Aux);
  }

  if(d[1]<d[2])  second=train(Aux1);
 }

 for( train::iterator i=second.begin(); i!=second.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << "->";
  std::cout << std::endl;
 }

 std::cout << cust(second) << std::endl;


 return 0;
}
