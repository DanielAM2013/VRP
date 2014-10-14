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

  void print( int i=0) {
   if(i==0)
    for( num k=0; k<size(); k++) {
     for( num s=0; s<size(); s++)
      cout << connected(k,s);
     cout << endl;
    }
   else
   for( num k=0; k<R.size(); k++)
    cout << R[k] << " ";
   cout << endl;
  }

  vector<point> read( char file[]) {
   ifstream data( file, ifstream::in);
   point aux;
   vector<point> Aux;
   while( data >> aux.real() >> aux.imag()) {
    Aux.push_back(aux);
   }
   return Aux;
  }

  grafo ( char file[]) {
   R=read(file);
   M=madj(R.size());
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

  void planar( void) {
   for( num i=0; i<R.size(); i++) {
    for( num j=0; j<R.size(); j++) {
     M.E[i][j]=dist(R[i],R[j]);
    }
   }
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

void grafo::CHRISTOFIDES(void) {

 madj AUX;
 // Aplica o KRUSKAL para determinar a minima espassão em árvore

 // encontrar vertices com grau impar
 // encontrar o "perfect matching" com peso mínimo dos vértices impares
 // 



}

//void grafo::PERFECT_MATCHING(void) {


//}




int main()
{
// grafo X(5);
 char file[]="points.dat";
 grafo X(file);
 X.planar();

// vector<bool> mark(X.size());

// X.insert(3,7);
// cout << X.in_loop(3, 3, 3, mark) << endl;
// X.insert(0,3);
// cout << X.in_loop(0, 0, 0, mark) << endl;
// X.insert(0,7);
// cout << X.in_loop(0, 0, 0, mark) << endl;

// X.print(0);
 X.KRUSKAL(); 
// X.insert(5,9);
//  cout << X.getw(1,3) << endl;
  X.print(0);
 for( num k=0; k<X.size(); k++)
  if( X.degre(k)%2==1)
   cout << X.degre(k) << endl;
 return 0;
}

