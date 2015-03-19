#include "madj.hpp"
#include <queue>

// inicializar grafo

class grafo {
 private:
  madj M;
// Como o número de vértice é finito podemos associar a cada vértice um valor sobre um conjunto,
// basta definir os elementos desse conjunto como a variável point;
  vector<point> R;

 public:
  grafo ( num n) {
   M=madj(n);
  }

  grafo ( char file[]) {
   R=vector<point>(read(file));
   M.geometric(R);
  }

  grafo ( vector<point> P) {
   R=vector<point>(P);
   M.geometric(P);
  }

  void print( int s=0) {
   M.print(s);
  }

  vertex enu( point x) {
   for( num k=0; k<R.size(); k++)
    if( x==R[k]) return k;
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

  void connect( vertex i, vertex j) {
   M.V[i][j]=M.V[j][i]=true;
  }

  void insert( vertex i, vertex j) {
   M.V[i][j]=M.V[j][i]=true;
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

  point node( vertex i) {
   return R[i];
  }

  void CHRISTOFIDES(void);
  void PERFECT_MATCHING(void);
 
  void save( char file[]) {
   ofstream saida( file);

   for( num k=0; k<size()-1; k++) {
    for( num t=k+1; t<size(); t++) {
     if( connected(k,t)) {
      saida << node(k).real() << " " << node(k).imag() << endl;
      saida << node(t).real() << " " << node(t).imag() << endl;
      saida  << endl;
     }
    }
   }
  }

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
//  cout << v << "->" << w << " " << aux << endl;

  if(aux==INF) return;

  AUX[v][w]=AUX[w][v]=true;
  insert(v, w);
//  cout << endl << "check loop" << endl;
  if(in_loop(v, v, v, Aux) ) {
//  if( !AuX[v] | !AuX[w]) 
//   insert(v,w);
//   cout << "loop" << endl;
   remove(v,w);
  }
//  else
//   continue;
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
 vector<point> odd_degree;
 for( num i=0; i<size(); i++) {
  if( degre(i)%2==1) {
   odd_degree.push_back(R[i]);
  }
 }

 for( num k=0; k<size()-1; k++)
  for( num t=k+1; t<size(); t++) 
   M.V[k][t]=M.V[t][k]=false;


// char out[]="output.dat";
// ofstream saida( out);

// for( num k=0; k<odd_degree.size(); k++) 
//  saida << odd_degree[k].real() << " " << odd_degree[k].imag() << endl;

// this->grafo(odd_degree);

 // encontrar o "perfect matching" com peso mínimo dos vértices impares
 // obs: usar o mesmo passo do KRUSKAL
// madj Aux(odd_degree);

 vector<bool> visited(size());
 for( num k=0; k<odd_degree.size()*(odd_degree.size()-1)/2; k++) {
  double aux=INF;
  vertex v=0, w=0;
  for( num i=0; i<odd_degree.size()-1; i++) {
   vertex p=enu(odd_degree[i]);
   for( num j=i+1; j<odd_degree.size(); j++) {
    vertex q=enu(odd_degree[j]);
    if( connected(p,q)) break;
    if(getw(p,q) < aux & !visited[q] & !visited[p]) {
     v=p; w=q; aux=getw(q,p);
    }
   }
  }
//  cout << v << "<->" << w << endl;
  if(aux==INF) break;
  if( !visited[v] & !visited[w]) {
   connect(v, w);
   visited[v]=visited[w]=true;
  }
  
 }
 // Selecionar um circuito de Euler
 // Usar pesquisa usando DFS para encontrar um circuito de Euler, uma dúvida trivial é se pode
 // existir mais de um circuito no grafo.
// for( num k=0; k<size(); k++) {
  
// }

}



//void grafo::PERFECT_MATCHING(void) {


//}
/*
int main()
{
// grafo X(5);
 char file[]="points.dat";
 grafo X(file);

 vector<bool> mark(X.size());

// X.insert(3,7);
// cout << X.in_loop(3, 3, 3, mark) << endl;
// X.insert(0,3);
// cout << X.in_loop(0, 0, 0, mark) << endl;
// X.insert(0,7);

// cout << X.enu(X.node(15)) << " " << X.node(15) << endl;

 X.KRUSKAL(); 
// X.CHRISTOFIDES();
// for( num k=0; k<X.size(); k++) {
//  if(X.in_loop(k, k, k, mark)) cout << k << endl;
// }

 char out[]="output.dat";
 X.save(out);

// X.print(0);
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
 system("gnuplot -p -e "
 return 0;
}
*/
