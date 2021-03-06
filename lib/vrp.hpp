#include <iostream>
#include <fstream>
#include <complex>
#include <vector>


typedef std::complex<double> point;
typedef std::vector<point> route;
typedef std::vector<route> train;

typedef unsigned vertex;
typedef unsigned num;


typedef double weight;

/*
#ifndef _VRP_
#define _VRP_

template < class graph >
class vrp {
 private:
  graph G;
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


#endif
*/
