#ifndef _MADJ_
#define _MADJ_

#include "route.hpp"

#define INF (1e+30)
using namespace std;

class madj
{
 private:

  vector<point> N;
  vector<vector<weight> > E;
  vector<vector<bool> > V;
  num dim;
  
 public:

 route getN () ;
 vector<vector<weight> > getE () ;
 vector<vector<bool> > getV () ;

 madj ( num) ;
 madj ( const madj& ) ;
 madj ( route) ;

 void insert_arc ( vertex, vertex, weight) ;
 void remote_arc ( vertex, vertex) ; 
 void print (int choise) ;
 double dist ( point x, point y) ;
 void geometric ( route) ;
 num in_degree ( vertex v) ;
 num out_degree ( vertex v) ;
 bool connected ( vertex, vertex) ;

 friend class grafo;
};
#endif
