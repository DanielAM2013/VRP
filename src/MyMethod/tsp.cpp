#include "vrp.hpp"

/*
 Seja R um conjunto de pontos em $\mathbb{R}^2$
 \begin{enumerate}
 \item Tome R(1)=D(1);
 \item Tome R(2)=ponto de $D-R$ mais próximo de R.
 \item Pare quando $D-R=\emptyset$ 
 \end{enumerate}
*/

// Retorna o menor custo para adicionar P a R entre near e near++
double closer(point P, route R, int& near)
{
 double d[2];
 d[1]=1e+32;

 int i;
 for( i=0; i<R.size()-1; i++) {
  d[0]=std::abs(P-R[i])+std::abs(P-R[i+1])-std::abs(R[i]-R[i+1]);
  if(d[0]<d[1]) {
   d[1]=d[0];
   near=i;
  }
 }
 d[0]=std::abs(P-R[R.size()-1])+std::abs(P-R[0])-std::abs(R[R.size()-1]-R[0]);
 if(d[0]<d[1]) {
  d[1]=d[0];
  near=R.size()-1;
 }

 return d[1];
};

// Suponto $P\cap R = \emptyset$
// Retorna o menor custo ao adicionar um ponto pos de P a R entre near e near++
double point_closer(route P, route R, int& aux, int &pos) {

 double d[2];

 for( int i=0; i<R.size(); i++) {
  d[0]=closer(P[i], R, aux);
  if(d[0]<d[1] & 0<d[0]) {
   d[1]=d[0];
   pos=i;
  }
 }

 return d[1];
}

double tsp(route R, route& S) 
{
 route Aux=R;
 S.clear();

 S.push_back(R[0]);

 int pos[2];
 double dist;

 dist=point_closer(R, aux, pos[0], pos[1]);

 s.push_back(R[pos[1]]);
  
}

/*
void tsp(route **R) {

 double d[2];
 aux = *R;

 while(aux) {
  d[1]=1e+30;
  for(route *i=aux->next; i!=NULL; i=i->next) {
   for( route *j=*R; j!=aux; j=j->next) {
    d[0]=d(R,j)+d(i,R)-d(i,j);
    if(d[0]<d[1]) {
     d[1]=d[0];
     // Trocar i com j em route;
     i->prev->next=j;
     i->next->prev=j

     j->prev->next=i;
     j->next->prev=i;
    }
   } 
  }
 }
}
*/
int main()
{

 std::ifstream data("points.dat", std::ifstream::in);
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 

 point X(-0.001,0.999);
 double dist;
 int x;


// std::sort (first.begin(), first.end(), operator<);

// for ( int i = 0; i < first.size(); i++) std::cout << first[i] << std::endl;



 route test;
 test.push_back(first[0]);
 test.push_back(first[1]);
 test.push_back(first[2]);

 for ( int i = 0; i < test.size(); i++) std::cout << test[i] << std::endl;

 dist= closer(X, test, x);
 std::cout << dist << test[x] << X << std::endl;


 return 0;
}
