#include "../../lib/basic.hpp"

typedef double weight;

using namespace std;

typedef list<vertex> V;
typedef list<weight> W;

class ladj
{
 private:
  vector<V> N;
  vector<W> E;
  num dim;
 
 public:

  ladj ( num n);

  void insert_arc ( vertex, vertex, weight) ;
  void remove_arc ( vertex, vertex, weight) ;
  void print () ;


  bool in_lopp ( vertex) ;
  friend void mst ( ladj);
  friend V::iterator mw ( ladj);
};
