#include "basic.hpp"
#include <vector>

class matriz_adj
{
// private:
 public:
 std::vector<std::vector<bool> > M;
 num dim;

 matriz_adj(num m) {
  dim=m;

  for( num i=0; i<dim; i++) {
   std::vector<bool> aux;
   for( num j=0; j<dim; j++) {
    aux.push_back(false);
   }
   M.push_back(aux);
  }
 }

// Primeira questão
 num outdeg( vertex v) {
  num aux=0;
  for( vertex i=0; i<dim; i++) aux+=(num) M[v][i];
  return aux;
 }

 num indeg( vertex v) {
  num aux=0;
  for( num i=0; i<dim; i++) aux+=(num) M[i][v];
  return aux;
 }

 void insert_arc( vertex i, vertex j) {
  M[i][j]=true;
 }

// Segunda questão
 void insert( vertex v, vertex w) {
  insert_arc(v,w);
  insert_arc(w,v); 
 }

 void remove_arc( vertex v, vertex w) {
  M[v][w]=false;
 }

// Terceira questão
 void remove( vertex v, vertex w) {
  remove_arc( v, w);
  remove_arc( w, v);
 }

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
 bool arc_adj( vertex v, vertex w) {
  return M[v][w];
 }
// Oitava questão
 list_adj conv_list_adj(void);
 arcs conv_arcs(void);

// Nona questão
 void Rand( num Max, num A) {
  srand(time(NULL));
  for( num i=0; i<A; i++) {
   insert(rand()%Max, rand()%Max);
  }
 }

// Decima Terceira questão 
 int isArb( void) {
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

  void Arb_rand( num Son) {

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


 void print(void) {
  for( num i=0; i<dim; i++) {
   for( num j=0; j<dim; j++) {
    std::cout << M[i][j] << " ";
   }
   std::cout << std::endl;
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

void print_vector( std::vector<bool> cache) {

 for( num i=0; i<cache.size(); i++) {
  std::cout << cache[i];
 }
 std::cout << std::endl;
}


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
//   std::cout << i << "->" << j << std::endl;
   std::cout << j << " ";
//   print_vector(cache);
   // Reaplica o algortimo para "j"
   DFS( A, j, cache);
   cache[j]=false;
   std::cout << std::endl;
  }
 }
}


int main()
{

 matriz_adj A(4);
// Teste: Segunda questão
 A.insert_arc(0,1);
 A.insert_arc(0,2);
 A.insert_arc(0,3);
 
 A.insert_arc(1,0);
 A.insert_arc(1,2);
 A.insert_arc(1,3);

 A.insert_arc(2,0);
 A.insert_arc(2,1);
 A.insert_arc(2,3);

 A.insert_arc(3,0);
 A.insert_arc(3,1);
 A.insert_arc(3,2);


// A.insert_arc(3,0);

// A.insert_arc(3,4);
// A.insert_arc(4,5);
// A.insert_arc(5,6);
// A.insert_arc(6,7);
// A.insert_arc(7,8);
// A.insert_arc(8,9);
// A.insert_arc(9,0);

// Teste: primeira questão
// std::cout << A.indeg(5) << std::endl;
// std::cout << A.outdeg(5) << std::endl;

// Teste: terceira questão
// A.remove_arc(0,1);

// Teste: sexta questão
// if( A.hasloop()) std::cout << "ok";

 std::vector<bool> cache;
 
 for( num i=0; i<A.dim; i++) cache.push_back(false);

 cache[0]=true;
 DFS(A,0,cache);
 A.print();


// matriz_adj A(10);
// A.Arb_rand(1);
// std::cout << A.isArb();
// A.Dijkstra(1);
// A.print();

 return 0;
}


