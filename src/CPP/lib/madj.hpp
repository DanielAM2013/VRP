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
 protected:
  
 public:

 madj( num);
 madj( vector<point>);

 route 

 void insert_arc ( vertex, vertex, weight) ;
 void remote_arc ( vertex, vertex) ; 
 void print (int choise) ;
 double dist ( point x, point y) ;
 void geometric ( vector<point>) ;
 num in_degree ( vertex v) ;
 num out_degree ( vertex v) ;
 bool connected ( vertex, vertex) ;

 friend class grafo;
};
