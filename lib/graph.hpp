#ifndef _GRAPH_
#define _GRAPH_

#include "base.hpp"

template< class graph_t>
class graph {
 private:
  graph_t M;
  std::vector<point> R;

 public:
  graph ( num ) ;
  graph ( char file[]) ;
  graph ( route P) ;
  void print ( int ) ;
  vertex enu ( point ) ;
  num degre(vertex v) ;
  weight dist ( point , point ) ;
  void connect ( vertex , vertex ) ;
  void insert ( vertex , vertex ) ;
  void insert ( vertex ,  vertex , weight ) ;
  void remove ( vertex , vertex ) ;
  bool in_loop ( vertex, vertex, vertex, std::vector<bool>&);
  void KRUSKAL () ;
  bool connected ( vertex, vertex ) ;
  num size () ;
  weight getw ( vertex , vertex ) ;
  point node ( vertex ) ;
  void CHRISTOFIDES () ;
  void PERFECT_MATCHING () ;
  void save ( char file[]) ;
};
#endif
