// Representação de um grafo através de matrizes de adjacência
// Criar uma estrutura básica e universal para manipulação de grafos
// 

#include "../lib/basic.hpp"

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

 madj(num m=0) {
  dim=m;
  V=vector<vector<bool> >(m);
  E=vector<vector<weight> >(m);
  N=vector<point>(m);
  for( num i=0; i<m; i++) {
   V[i]=vector<bool>(dim);
   E[i]=vector<weight>(dim); 
  }
 }

 madj( vector<point> P) {
   geometric(P);
 }

 void insert_arc( vertex i, vertex j, weight w=INF) {
  V[i][j]=true;
  E[i][j]=w;
 }

 void remote_arc( vertex v, vertex w) {
  V[v][w]=false;
  E[v][w]=INF;
 }

 void print(int choise=0) {
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

 double dist( point x, point y) {
  return abs(x-y);
 }

 void geometric( vector<point> P) {
//  this->~madj();
  *this=madj(P.size());
  N=P;
  for( num i=0; i<P.size(); i++) {
   for( num j=0; j<P.size(); j++) {
    E[i][j]=dist(P[i],P[j]);
    V[i][j]=false;
   }
  }
 }

 num in_degree( vertex v) {
  num aux=0;
  for( num i=0; i<dim; i++) aux+=(num) V[i][v];
  return aux;
 }

 num out_degree( vertex v) {
  num aux=0;
  for( num i=0; i<dim; i++) aux+=(num) V[v][i];
  return aux;
 }
 
 bool connected( vertex v, vertex w) {
  return V[v][w];
 }



/*


// Sexta questão
 bool hasloop( void) {
  num D=dim;
  for( num k=0; k<D; k++) {
   bool Aux[D];
   for( num i=0; i<D; i++) Aux[i]=false;

   std::queue<num> cache;

   cache.push(k);
   Aux[k]=true;

   while(!cache.empty()) {
    vertex v=cache.front();
    for( vertex j=0; j<D; j++) {
     if( arc_adj( v, j)) {
      if( Aux[j]) return true;
      else {
       cache.push(j);
       Aux[j]=true;
      }   
     }   
    }   
    cache.pop();
   }   
  }
  return false;
 }

// Sétima questão
 bool has_arc( vertex v, vertex w) {
  return M[v][w];
 }

// Oitava questão
 list_adj conv_list_adj(void);
 arcs conv_arcs(void);

// Decima Terceira questão 
 int is_arb( void) {
  num null=0;
  int aux;

  for( vertex i=0; i<dim; i++) {
   if( indeg(i)>1) return -1;
   if( indeg(i)==0) {
    null++;
    aux=i;
   }
  }
  if(null==1) return aux;
  else return -1;
 }

  void arb_rand( num Son) {

  srand(time(NULL));
  bool cache[dim];
  for( num i=0; i<dim; i++) cache[i]=false;

  cache[rand()%dim]=true;

  for( num t=0; t<dim*dim; t++)
  for( num i=0; i<dim; i++) {
   for( num j=0; j<Son; j++) {
    num k=rand()%dim;
    if( !cache[k] & cache[i] ) {
      insert_arc(i,k);
      cache[k]=true;
    }
   }
  }
 }

// Decima sétima questão
 num Dist( vertex s) {
  num Inf = dim;

  num dist[dim];

  std::queue<vertex> fila;

  for ( vertex v = 0; v < dim; v++)
   dist[v] = Inf;

  dist[s] = 0;
  fila.push(s);

  while (!fila.empty()) {
   vertex v=fila.front();

   for( vertex w = 0; w <dim; w++)
    if( M[v][w] && dist[w]==Inf ) { 
     dist[w] = dist[v] + 1;
     fila.push(w);
     std::cout << "dist(" << v << "," << w << ")=" << dist[w];
    }

   fila.pop();
  }
 }


 void BFS( vertex o) {

  bool Aux[dim];
  for( num i=0; i<dim; i++) Aux[i]=false;

  std::queue<num> cache;

  cache.push(o);

  while(!cache.empty()) {
   vertex v=cache.front();
   for( vertex j=0; j<dim; j++) {
    if( M[v][j] & !Aux[j]) {
     cache.push(j);
     Aux[j]=true;
     std::cout << v << "->" << j << std::endl;
    }
   }
   cache.pop();
  }
 }

 void Dijkstra( vertex s) { 

  num Inf=dim;
  vertex p[2]; 
  
  num dist[dim];
  int parent[dim];

   for( num w=0; w<dim; w++) {
    dist[w]  = Inf;
    parent[w]=-1;
   }

   parent[s] = s;
   dist[s] = 0; 

   while (1) {

      num min = Inf;
      for( num v = 0; v<dim; v++) 
         if( parent[v]!=-1) 
            for( num w=0; w<dim; w++)    
                if( parent[w]==-1 & min > dist[v]+(num) M[v][w]) {
                  min=dist[v]+(num) M[v][w];    
                  p[0]=v, p[1]=w;
               }
      if( min==Inf) break; 
      parent[p[1]] = p[0]; 
      dist[p[1]] = min;

   }   

   for( num v=0; v<dim; v++)
        std::cout << v << ":" << parent[v] << ":" << dist[v] << std::endl;
 }

};

// Realiza a busca em profundidade
// A: dígrafo como matriz de adjacência
// i: vertíce inicial
// cache: vetor de vértices já vizitados
void DFS( matriz_adj A, num i, std::vector<bool>& cache)
{
 // Varre todos os vértices
 for( num j=0; j<A.dim; j++) {
  // Verifica há conexão de "i" para "j", e se "j" ainda não foi marcado
  if(A.M[i][j] & !cache[j]) {
   // Marca "j" como já visitado
   cache[j]=true;
   // Mostra a conexão na tela
   std::cout << i << "->" << j << std::endl;
   // Reaplica o algortimo para "j"
   DFS( A, j, cache);
  }
 }
*/
 friend class grafo;
// friend bool in_loop( grafo, vertex, vector<bool>&);
};
/*
int main()
{
 char file[]="points.dat";
 vector<point> R=read(file);

// for( num i=0; i<R.size(); i++) 
//  cout << R[i];
// cout << endl;

 madj A;
 A.geometric(R);


// A.insert_arc(0,1);
// cout << A.in_degree(0)  << " " << A.out_degree(0) << endl;
 
 A.print(0);

 return 0;
}
*/
