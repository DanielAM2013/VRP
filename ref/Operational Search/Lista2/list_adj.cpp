//#include "basic.hpp"

typedef std::list< std::list<vertex> > LA;

class list_adj
{
 public:
 LA g;
 num dim;

 list_adj( num V) {

  dim=V;

  for( num i=0; i<V; i++) {
   std::list<vertex>  aux;

   aux.push_back(i);

   g.push_back(aux);
  }
 }

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
 void insert_arc( vertex in, vertex out) {
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   if( *(i->begin()) == in) {
    i->push_back(out);
    return;
   }
  }
 }

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

 void print(void) {
  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   std::cout << *(i->begin()) << ":";
   for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
    std::cout << *j << " ";
   }
   std::cout << std::endl;
  }
 }

};

/*
int main()
{
 list_adj A(10);
// Teste: segunda questão
 A.insert_arc(0,1);
 A.insert_arc(1,2);
 A.insert_arc(2,3);
 A.insert_arc(3,4);
 A.insert_arc(4,5); 
 A.insert_arc(5,6);
 A.insert_arc(6,7);
 A.insert_arc(7,8);
 A.insert_arc(8,9);
// A.insert_arc(9,0);

// Teste: primeira questão
 std::cout << A.indeg(0) << std::endl;
 std::cout << A.outdeg(0) << std::endl;
// Teste: terceira questão
// A.remove_arc(0,1);
// A.BFS(1);

 if(A.hasloop()) std::cout << "ok";

 A.print();

 return 0;
}

*/
