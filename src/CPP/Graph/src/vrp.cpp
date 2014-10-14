#include "madj.cpp"
#include <queue>

// inicializar grafo

class grafo {
 private:
  madj M;
  vector<point> R;

 public:
  grafo ( num n) {
   M=madj(n);
  }

  grafo ( char file[]) {
   vector<point> Aux=read(file);
   M.geometric(Aux);
  }

  grafo ( vector<point> P) {
   M.geometric(P);
  }

  void print( int s=0) {
   M.print(s);
  }

  num degre(vertex v) {
   num aux=0;
   for( num k=0; k<size(); k++) 
    aux+=connected(v,k);
   return aux;
  }

  weight dist( point x, point y) {
   return abs(x-y);
  }

  void insert( vertex i, vertex j) {
   M.V[i][j]=true; M.V[j][i]=true;
  }
  void insert( vertex i,  vertex j, weight w) {
   M.V[i][j]=true; M.V[j][i]=true;
   M.E[i][j]=M.E[j][i]=w;
  }

  void remove( vertex i, vertex j) {
   M.V[i][j]=false; M.V[j][i]=false;
  }


  bool in_loop( vertex, vertex, vertex, vector<bool>&);

  void KRUSKAL( void);

  bool connected( vertex i, vertex j ) {
   return M.V[i][j];
  }

  num size( void) {
   return M.dim;
  }

  weight getw( vertex i, vertex j) {
   return M.E[i][j];
  }

  void CHRISTOFIDES(void);
  void PERFECT_MATCHING(void);
 
};

bool grafo::in_loop(vertex i, vertex origin, vertex prev, vector<bool>& visited) {
 visited[i]=true;

// for( num k=0; k<size(); k++) cout << visited[k];
// cout << endl << "--------------" << endl;

 for( num j=0; j<size(); j++) 
  if( connected(i,j) & j!=i & j!=prev) {
   if( visited[j]) {
    if(j==origin) {
//     cout << i << "->" << j << endl;
     return true;
    }
    else continue;
   }
   else {
//     cout << i << "->" << j << endl;
     if(this->in_loop(j, origin, i, visited)) return true;
   }
  }

 visited[i]=false;
 return false;
}


void grafo::KRUSKAL(void)
{
 // pesquisa entre as arestas não ligadas a com menor peso e que não gere loop
 vector<bool> AuX(size());
 vector<vector<bool> > AUX(size());

 num N=size();

 for( num k=0; k<size()-1; k++) {
  AUX[k]=vector<bool>(size());
  for( num t=k+1; t<size(); t++)
   if(connected(k,t)) {
    AUX[k][t]=AUX[t][k]=AuX[k]=AuX[t]=true;
    N-=2;
   }
 }

 while(N>0)
// for( num s=0; s<100*199; s++)
 { 
  vector<bool> Aux(size());
  weight aux=INF;
  vertex v=0, w=0;

  for( num i=0; i<size()-1; i++)
   for( num j=i+1; j<size(); j++)
    if( !AUX[i][j] & getw(i,j) < aux) {
     aux=getw(i,j);
     v=i; w=j;
   }
  cout << v << "->" << w << " " << aux << endl;

  if(aux==INF) return;

  insert(v,w);
  AUX[v][w]=AUX[w][v]=true;
//  cout << endl << "check loop" << endl;
  if(in_loop(v, v, v, Aux) ) {
   cout << "loop" << endl;
   remove(v,w);
   continue;
  }
//  cout << endl << "end ckeck loop" << endl;
  if( !AuX[v]) N--;
  if( !AuX[w]) N--;
  AuX[v]=AuX[w]=true;
//  for( num s=0; s<size(); s++)
//   cout << AuX[s];
//  cout << endl;
//  cout << k << endl;
 }
}

//#include <boost/numeric/ublas/matrix.hpp>
//#include <boost/numeric/ublas/io.hpp>


void grafo::CHRISTOFIDES(void) {

 // Aplica o KRUSKAL para determinar a minima espassão em árvore
 KRUSKAL();

 // encontrar vertices com grau impar
 vector<point> odd_degre;
 for( num i=0; i<size(); i++) {
  if( degre(i)%2==1) {
   odd_degre.push_back(R[i]);
  }
 }

 // encontrar o "perfect matching" com peso mínimo dos vértices impares
 // obs: usar o mesmo passo do KRUSKAL
 madj Aux(odd_degre);
 vector<bool> visited(size());
 for( num k=0; k<odd_degree.size(); k++) {
  double aux=INF;
  vertex v=0, w=0;
  for( num i=0; i<odd_degre.size(); i++)
   for( num j=0; j<odd_degre.size(); j++) {
    if( !Aux.connected(i,j) & getw(i,j) < aux) {
     v=i; w=j; aux=getw(i,j);
    }
   }
  if(aux==INF) break; 
  if( mark[v] & mark[w]) continue;
  


 }


 // Selecionar um circuito de Euler

}

//void grafo::PERFECT_MATCHING(void) {


//}

int main()
{
// grafo X(5);
 char file[]="points.dat";
 grafo X(file);

// vector<bool> mark(X.size());

// X.insert(3,7);
// cout << X.in_loop(3, 3, 3, mark) << endl;
// X.insert(0,3);
// cout << X.in_loop(0, 0, 0, mark) << endl;
// X.insert(0,7);
// cout << X.in_loop(0, 0, 0, mark) << endl;

// X.print(0);
// X.KRUSKAL(); 
// X.insert(5,9);
//  cout << X.getw(1,3) << endl;
//  X.print(0);
// for( num k=0; k<X.size(); k++)
//  if( X.degre(k)%2==1)
//   cout << X.degre(k) << endl;


// using namespace boost::numeric::ublas;
//    matrix<double> m (3, 3);
//    for (unsigned i = 0; i < m.size1 (); ++ i)
//        for (unsigned j = 0; j < m.size2 (); ++ j)
//            m (i, j) = 3 * i + j;
//    std::cout << m << std::endl;

 return 0;
}

