#include "madj.hpp"

vector<point> madj::getN () {
 return this->N;
}

vector<vector<weight> > madj::getE () {
 return this->E;
}

vector<vector<bool> > madj::getV () {
 return this->V;
}

madj::madj ( const madj& A) {
 N=vector<point> (A.N);
 E=vector<vector<weight> >(A.E);
 V=vector<vector<bool> > (A.V); 
 dim=N.size();
}

madj::madj (num m=0) {
 dim=m;
 V=vector<vector<bool> >(m);
 E=vector<vector<weight> >(m);
 N=vector<point>(m);
 for( num i=0; i<m; i++) {
  V[i]=vector<bool>(dim);
  E[i]=vector<weight>(dim); 
 }
}

madj::madj ( vector<point> P) {
  geometric(P);
}

void madj::insert_arc ( vertex i, vertex j, weight w=INF) {
 V[i][j]=true;
 E[i][j]=w;
}

void madj::remote_arc ( vertex v, vertex w) {
 V[v][w]=false;
 E[v][w]=INF;
}

void madj::print(int choise=0) {
 switch (choise) {
  case 0:
   for( num i=0; i<E.size(); i++) {
    for( num j=0; j<E.size(); j++)
     cout << V[i][j] << " ";
    cout << endl;
   }
   break;
  case 1:
   for( num i=0; i<E.size(); i++) {
    for( num j=0; j<E.size(); j++)
     cout << " " << E[i][j];
    cout << endl;
   }
   break;
  case 2:
   for( num i=0; i<N.size(); i++) {
    for( num j=0; j<N.size(); j++) {
     cout << "(" << V[i][j] << "," << E[i][j] << ")" << " ";
    }
    std::cout << std::endl;
   }
  break;
 }
}

double madj::dist( point x, point y) {
 return abs(x-y);
}

void madj::geometric( vector<point> P) {
 *this=madj(P.size());
 N=P;
 for( num i=0; i<P.size(); i++) {
  for( num j=0; j<P.size(); j++) {
   E[i][j]=dist(P[i],P[j]);
   V[i][j]=false;
  }
 }
}

num madj::in_degree( vertex v) {
 num aux=0;
 for( num i=0; i<dim; i++) aux+=(num) V[i][v];
 return aux;
}

num madj::out_degree( vertex v) {
 num aux=0;
 for( num i=0; i<dim; i++) aux+=(num) V[v][i];
 return aux;
}
 
bool madj::connected( vertex v, vertex w) {
 return V[v][w];
}
