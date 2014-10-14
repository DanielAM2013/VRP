#include "../lib/basic.hpp"

typedef double weight;

using namespace std;

typedef list<vertex> V;
typedef list<weight> W;

class ladj
{
 private:
 // Estrutura para representar o grafo;
 // Cada indice do vetor "G" indica o vertices;
 // 
  vector<V> N;
  vector<W> E;
  num dim;
 
 public:

  ladj( num n) {
   dim=n;
   N=vector<V>(n);
   E=vector<W>(n);
  }

  // para identificar cada "vertex" com um "point"

  void insert_arc( vertex in, vertex out, weight w) {
   N[in].push_back(out);
   E[in].push_back(w);
  }

  void remove_arc( vertex in, vertex out, weight w) {
   W::iterator j=E[in].begin();
   for( V::iterator i=N[in].begin(); i!=N[in].end(); i++) {
    if( *i==out & *j==w) {
     N[in].erase(i);
     E[in].erase(j);
     return;
    }
    j++;
   }
  }

  void print(void) {

   for( vertex i=0; i<dim; i++) {
    cout << i << ":";

    W::iterator k=E[i].begin();
    for( V::iterator j=N[i].begin(); j!=N[i].end(); j++) {
     cout << "(" << *j << "," << *k << ")";
    }
    k++;
    cout << endl;
   }
  }


  bool in_lopp( vertex o) {
   bool Aux[dim];
   for( num i=0; i<dim; i++) Aux[i]=false;

   std::queue<num> cache;

   cache.push(o);

   while(!cache.empty()) {
    vertex v=cache.front();
    for( vertex j=0; j<dim; j++) {
     if( arc_adj( v, j) & !Aux[j]) {
      cache.push(j);
      Aux[j]=true;
      std::cout << v << "->" << j << std::endl;
     }   
    }   
    cache.pop();
   }
  }

/*
// Primeira questão
 num indeg( vertex v) {
  num aux=0;
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
    if( *j==v) aux++;
   }
  }
  return aux;
 }

 num outdeg( vertex v) {
  num aux=0;
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   if( *(i->begin())==v) {
    aux=i->size()-1;
   }
  }
  return aux;
 }
//-----------------------------------------------

// Segunda questão
 void insert( vertex in, vertex out) {
  insert_arc( in, out);
  insert_arc( out, in);
 }

 void remove_arc( vertex in, vertex out) {
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   if( *(i->begin()) == in) {
    for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
     if( *j==out) i->erase(j++);
     return;
    }
   }
  }
 }

// Terceira questão
 void remove( vertex in, vertex out) {
  remove_arc( in, out);
  remove_arc( out, in);
 }

// Sexta questão, item 1
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

// Sexta questão, item 2
 bool paralell_arc( void) {
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
    for( std::list<vertex>::iterator k=++j; j!=i->end(); j++) {
     if( *j==*k) return true;
    }
   }
  }
  return false;
 }

// Sétima questão
 bool arc_adj( vertex in, vertex out) {
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   if( *(i->begin())==in)
    for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
     if( *j==out) return true;
    }
  }
  return false;
 }
// Oitava questão
  arcs conv_arcs( void);
  matriz_adj conv_matriz_adj( void);

// Nona questão
 void Rand( num Max, num A) {
  srand(time(NULL));
  for( num i=0; i<A; i++) {
   insert(rand()%Max,rand()%Max);
  }
 }

// Décima sexta questão
 void BFS( vertex o) {
  num D=dim;
  bool Aux[D];
  for( num i=0; i<D; i++) Aux[i]=false;

  std::queue<num> cache;

  cache.push(o);

  while(!cache.empty()) {
   vertex v=cache.front();
   for( vertex j=0; j<D; j++) {
    if( arc_adj( v, j) & !Aux[j]) {
     cache.push(j);
     Aux[j]=true;
     std::cout << v << "->" << j << std::endl;
    }   
   }   
   cache.pop();
  }
 }

*/
 friend void mst( ladj);
 friend V::iterator mw( ladj);
};

void mst( ladj *G) {

 // ladj Aux(*G);
 // Lista de arestas 
 // return iterator for weight with smaller value


}





int main()
{
 ladj A(3);
// Teste: insert_arc 
 A.insert_arc( 0, 1, 0.1);
 A.insert_arc( 1, 2, 0.2);
 A.insert_arc( 2, 1, 0.3);
 
// Teste: remove_arc
 A.remove_arc( 1, 2, 0.2);

 mst(&A);

// Teste: print
 A.print();

 return 0;
}


