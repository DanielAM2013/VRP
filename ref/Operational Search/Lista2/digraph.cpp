#include "basic.hpp"
#include "arcs.cpp"
#include "matriz_adj.cpp"
#include "list_adj.cpp"

// vetor de arcos       : 1
// matriz de adjacência : 2
// lista de adjacência  : 3

matriz_adj arcs::conv_matriz_adj( void) {
 matriz_adj aux(dim);
 for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
  aux.insert_arc( i->orig, i->dest);  
 }
 return aux;
}

list_adj arcs::conv_list_adj( void) {
 list_adj aux(dim);
 for( std::list<arc>::iterator i=vect.begin(); i!=vect.end(); i++) {
  aux.insert_arc( i->orig, i->dest);
 }
 return aux;
}

list_adj matriz_adj::conv_list_adj( void) {

 list_adj Aux(dim);

 for( num i=0; i<dim; i++) {
  for( num j=0; j<dim; j++) {
   if( M[i][j]) Aux.insert_arc( i, j);
  }
 }
 return Aux;
}

arcs matriz_adj::conv_arcs( void) {
 arcs Aux(dim);

 for( num i=0; i<dim; i++) {
  for( num j=0; j<dim; j++) {
   if( M[i][j]) 
    Aux.insert_arc(i, j);
  }
 }
 return Aux;
}


matriz_adj list_adj::conv_matriz_adj( void) {

 matriz_adj aux(dim);

  for( LA::iterator i=g.begin(); i!=g.end(); i++) {
   for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
    aux.insert_arc(*(i->begin()), *j);
   }
  }
 return aux;
}

arcs list_adj::conv_arcs( void) {

 arcs Aux(dim);

 for( LA::iterator i=g.begin(); i!=g.end(); i++) {
  for( std::list<vertex>::iterator j=++i->begin(); j!=i->end(); j++) {
   Aux.insert_arc(*(i->begin()), *j);
  }
 }
 return Aux;
}


int main()
{

// Questão 11
// 0-1 1-2 1-3 3-4 3-5 1-6 0-7 7-8 7-9 8-6 
 matriz_adj A(9);

 A.insert_arc(0,1);
 A.insert_arc(1,2);
 A.insert_arc(1,3);
 A.insert_arc(3,4);
 A.insert_arc(3,5);
 A.insert_arc(1,6);
 A.insert_arc(0,7);
 A.insert_arc(7,8);
 A.insert_arc(7,9);
 A.insert_arc(8,6);

 std::vector<bool> cache;
 // Alocado dinamicamente
 for( num i=0; i<A.dim; i++) cache.push_back(false);

 DFS( A, 0, cache);
//   Saída
// 0->1
// 1->2
// 1->3
// 3->4
// 3->5
// 1->6
// 0->7
// 7->8


// Questão 14
// 8-9 3-7 1-4 7-8 0-5 5-2 3-8 2-9 0-6 4-9 2-6 6-4
 matriz_adj B(10);

 B.insert_arc( 8, 9);
 B.insert_arc( 3, 7);
 B.insert_arc( 1, 4);
 B.insert_arc( 7, 8);
 B.insert_arc( 0, 5);
 B.insert_arc( 5, 2);
 B.insert_arc( 3, 8);
 B.insert_arc( 2, 9);
 B.insert_arc( 0, 6);
 B.insert_arc( 4, 9);
 B.insert_arc( 2, 6);
 B.insert_arc( 6, 3);
 
 B.BFS(0);

// Saída
// 0->5
// 0->6
// 5->2
// 6->3
// 2->9
// 3->7
// 3->8

/*
// Teste: Oitava questão

 matriz_adj MA(10);

 MA.insert_arc(0,1);
 MA.insert_arc(1,2);
 MA.insert_arc(2,3);
 MA.insert_arc(3,4);
 MA.insert_arc(4,5);

 MA.print();
// vetor de arcos       : 1
// matriz de adjacência : 2
// lista de adjacência  : 3

 arcs Aux21=MA.conv_arcs();
// Aux21.print();

 list_adj Aux23=MA.conv_list_adj();
// Aux23.print();

 matriz_adj Aux13=Aux21.conv_matriz_adj();
// Aux13.print();

 list_adj Aux12=Aux21.conv_list_adj();
// Aux12.print();

 arcs Aux31=Aux23.conv_arcs();
// Aux31.print();

 matriz_adj Aux32=Aux23.conv_matriz_adj();
// Aux32.print();
*/







 return 0;
}
