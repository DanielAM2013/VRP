//#include "basic.hpp"
#include <iostream>
#include <list>

using namespace std; 
typedef unsigned int num;

template< class A, class B>
struct Association {
 A orig;
 B dest;
};


template< class A, class B>
class arcs
{
 private:
  typedef struct Association<A,B> arc;
  std::list<arc> vect;
 protected:

 public:

// Construtores
//  arcs( num D=0) {
//   vect=list<arc>(D);
//  }


// Primeira questão
 num indeg( B v) {
  num aux=0;
  for( list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   if( i->dest==v) aux++;
  }
  return aux;
 }

 num outdeg( A v) {
  num aux=0;
  for( list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   if( i->orig==v) aux++;
  }
  return aux;
 }

 void associate( A o, B d) {
  arc aux;
  aux.orig=o;
  aux.dest=d;
  vect.push_back(aux);
 }

 void disassociate( A o, B d) {
  for( list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   if( i->orig==o & i->dest==d)
    vect.erase(++i);
  }
 }

/*

 void remove_arc( vertex o, vertex d) {
  for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   if( i->orig==o & i->dest==d)
    vect.erase(i++);
  }
 }

// Terceira questão
 void remove( vertex o, vertex d ) {
  for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   if( (i->orig==o & i->dest==d) | (i->orig==d & i->dest==o) ) 
    vect.erase(i);
  }
 }

// Sexta questão
 bool hasloop( void) {
  num D=dim;
  for( num k=0; k<D; k++) {
   bool Aux[D];
   for( num i=0; i<D; i++) Aux[i]=false;

   std::queue<num> cache;

   cache.push(k);
   Aux[k]=true;

   while(!cache.empty()) {
    vertex v=cache.front();
    for( vertex j=0; j<D; j++) {
     if( arc_adj( v, j)) {
      if( Aux[j]) return true;
      else {
       cache.push(j);
       Aux[j]=true;
      }   
     }   
    }   
    cache.pop();
   }   
  }
  return false;
 }

 bool paralell_arc( void) {
  
  for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   for( std::list<arc>::iterator j=++i; j!=vect.end(); j++) {
    if( i->orig=j->orig & i->dest==j->dest ) return true;
   }
  }
  return false;
 }

// Sétima questão
 bool arc_adj( vertex o, vertex d) {
  for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   if( i->orig==o & i->dest==d) return true;
  }
  return false;
 }
// Oitava questão
 matriz_adj conv_matriz_adj(void);
 list_adj conv_list_adj(void);

// Nona questão
 void Rand( num Max, num A) {
  srand(time(NULL));
  for( num i=0; i<A; i++) {
   insert(rand()%Max,rand()%Max);
  }
 }


// Métodos auxiliares
 void print( void) {
  for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
   std::cout << i->orig << "->" << i->dest << std::endl;
  }
 }

 void BFS( vertex o) {
  bool Aux[dim];
  for( num i=0; i<dim; i++) Aux[i]=false;

  std::queue<num> cache;

  cache.push(o);

  while(!cache.empty()) {
   vertex v=cache.front();
   for( vertex j=0; j<dim; j++) {
    if( this->arc_adj( v, j) & !Aux[j]) {
     cache.push(j);
     Aux[j]=true;
     std::cout << v << "->" << j << std::endl;
    }   
   }   
   cache.pop();
  }
 }
*/
};


int main()
{
 struct Association<double, int> x;

// Teste: Segunda questão
// x.insert_arc(0,1);
// x.insert_arc(1,2);
// x.insert_arc(2,3);
// x.insert_arc(3,4);
// x.insert_arc(4,5);
// x.insert_arc(5,6);
// x.insert_arc(6,7);
// x.insert_arc(7,8);
// x.insert_arc(8,9);
// x.insert_arc(9,0);

// Teste: Primeira questão
// std::cout << x.indeg(0) << std::endl;
// std::cout << x.outdeg(0) << std::endl;

// Teste: Terceira questão
// x.remove_arc(0,1);

// Teste: Sexta questão
// if( x.hasloop()) std::cout << "ok";

// Teste: Sétima questão

// Teste: Oitava questão

// std::cout << x.dim << std::endl;



// Teste: BFS
// x.BFS(0);



// x.print();
 return 0;
}


