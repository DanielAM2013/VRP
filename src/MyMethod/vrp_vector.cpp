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

 route::iterator last=R->begin();
/*
 while(R->end()!=NULL) {

  ponto *closer[2]={NULL,NULL};

  d[1]=1e+30;
  for( ponto *i=last->next; i!=NULL; i=i->next) {
   for( ponto *j=R; j!=last; j=j->next) {

    d[0]=abs(j->coord-i->coord)+abs(i->coord-j->next->coord)-abs(j->coord-j->next->coord);

    if(d[0]<d[1]) {
     d[1]=d[0];
     closer[0]=i;
     closer[1]=j;
    }
   }

   d[0]=abs(last->coord-i->coord)+abs(i->coord-R->coord)-abs(last->coord-R->coord);

   if(d[0]<d[1]) {
    d[1]=d[0];
    closer[0]=i;
    closer[1]=last;
   }
  }

  d[2]+=d[1];

   if(closer[0]->next)
    closer[0]->next->prev=closer[0]->prev;
   closer[0]->prev->next=closer[0]->next;

   closer[0]->next=closer[1]->next;
   closer[0]->prev=closer[1];

   if(closer[1]->next) {
    closer[1]->next->prev=closer[0];
    closer[1]->next=closer[0];
   }
   if(closer[1]==last) last=last->next;

 }
*/
 return d[2];
}


int main()
{
 // Ler Arquivo
 char test[]="points.dat";

 // Alocar ponto em uma estrutura
 route first=read_file(test); 
 std::cout << first.size() << std::endl;

 int N=first.size();

// Ordenar
 std::sort( first.begin(), first.end(), operator<);
// Alocar
 train second;
 // Enviar um veículo para cada ponto
 for( int i=0; i<N; i++) {
  route aux;
  aux.push_back(first[i]);
  second.push_back(aux);
  aux.clear();
 }

 for( train::iterator i=second.begin(); i!=second.end(); ++i)
  for( route::iterator j=i->begin(); j!=i->end(); ++j)
   std::cout << *j << std::endl;

 route::iterator aux=(first.begin()+2);
 std::cout << *aux << "+++" << std::endl;
 first.erase(aux);

 for( train::iterator i=second.begin(); i!=second.end(); ++i)
  for( route::iterator j=i->begin(); j!=i->end(); ++j)
   std::cout << *j << std::endl;


 // Calcular custo para esta situação
/*
 double d[2]={cust(second),0};

 while(d[1]-d[0]) {
  for( train::iterator i=second.begin(); i!=second.end(); ++i) {
   // Copiar second para aux
   train aux(second);
   // Mesclar i e ++i;
   
  }
 }
*/












 return 0;
}
