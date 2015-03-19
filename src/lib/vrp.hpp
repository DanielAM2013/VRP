#include "madj.cpp"
#include <queue>

class grafo {
 private:
  madj M;
  vector<point> R;
 
 public:
  void print ();
  vertex enu ( point x);
  num degre ( vertex x);
  weight dist ( point x, point y);
  void connect ( vertex i, vertex j);
  void insert ( vertex , vertex );
  void insert ( vertex , vertex , weight );
  void remove ( vertex , vertex );
  bool in_loop ( vertex, vertex, vertex, vector<bool> );
  void KRUSKAL ( void );
  bool connected ( vertex , vertex );
  num size ();
  weight getw ( vertex , vertex );
  point node ( vertex ); 
  void CHISTOFIDES ();
  void PERFECT_MATCHING ();
  void save ( char file[] );
};


