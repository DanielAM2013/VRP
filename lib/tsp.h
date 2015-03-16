#include <iostream>
#include <fstream>
#include <complex>
#include <cstdlib>
#include <unistd.h>
#include <vector>

using namespace std;

/*! ponto:= lista encadeada de numeros complexos
   Representação de rota por lista encadeada
*/

typedef struct Ponto {
  complex<double> coord;

  struct Ponto* next;
  struct Ponto* prev;
} ponto;

/*!
   Nome: route
   Descrição: Representação de uma lista ordenada de rotas.
*/

typedef struct Route {
 ponto subroute; 

 struct Route* next;
 struct Route* prev;
} route;

void print_point(complex<double> c)
{
  cout << "(" << c.real() << "," << c.imag() << ")" << endl;
}

void print_list_simple(ponto* P)
{
 ponto* Aux;
 Aux=P;
 while(Aux) {
  print_point(Aux->coord);
  Aux=Aux->next;
 }
}

void print_list_duple(ponto* P)
{
 ponto *Aux=P;

 if(Aux!=NULL) {
  do {
   print_point(Aux->coord);
   Aux=Aux->next;
  } while(Aux!=P);
 }
}

ponto* read_file_points(char s[]) {

 ifstream data(s, ifstream::in);

 ponto *P=NULL, *Aux, *swap;
 complex<double> coord;

 if(data >> coord.real() >> coord.imag()) {

  P = new ponto;

  P->coord=coord;

  P->prev=NULL;
  P->next=NULL;
 }

 Aux=P;
 while(data >> coord.real() >> coord.imag()) {

  swap=Aux;
  Aux=Aux->next=new ponto;
  Aux->prev=swap;

  Aux->coord=coord;
 }
 Aux->next=NULL;

 return P;
}

double dist_route(ponto* route, complex<double> x, ponto** out) {
 
 ponto *Aux;
 double dist[2];

 Aux=route;
 dist[1]=1e+30;

 do {
  if(Aux->coord==x) {
   dist[1]=-1;
   *out=NULL;
   break;
  }

  dist[0]=abs(Aux->coord - x)+abs(Aux->next->coord - x)-abs(Aux->coord - Aux->next->coord);
  if(dist[0]<dist[1] ) {
    *out=Aux;
    dist[1]=dist[0];
  }
  Aux=Aux->next;
 } while(Aux!=route);

 return dist[1];
}


void del(ponto** P, complex<double> DEL) {
 ponto* Aux;
 Aux=*P;

 while(Aux) {

  if(Aux->coord==DEL) {

   if(Aux->prev) {

    if(Aux->next) {
     Aux->prev->next=Aux->next;
     Aux->next->prev=Aux->prev;
    }
    else {
     Aux->prev->next=NULL;
    }
    delete Aux;
   }
   else {
    if(Aux->next) {
     *P=(*P)->next;
      Aux->next->prev=NULL;
      delete Aux;
    }
    else {
     delete *P;
     *P=NULL;
    }
   }
   break;
  }
  Aux=Aux->next;
 }
}

double point_closer(ponto* route, ponto **P, ponto **out, ponto** nov)
{

 ponto* Aux[3];
 double dist[2];

 Aux[0]=*P;
 dist[1]=1e+30;

 while(Aux[0]) {

  dist[0]=dist_route(route, Aux[0]->coord, &Aux[1]);

  if(dist[0]<0) {
 
   Aux[0]=Aux[0]->next;
   continue;
  }

  if(dist[1]>dist[0]) {
   *nov=Aux[0];
   *out=Aux[1];
   dist[1]=dist[0];
  }
  Aux[0]=Aux[0]->next;
 }

 return dist[1];
}

void salve_file(ponto* route, char name_file[])
{
 ponto* Aux;
 ofstream out(name_file, ofstream::out);

 Aux=route;

 while(Aux!=NULL) {
  out << Aux->coord.real() << " " << Aux->coord.imag() << endl;
  Aux=Aux->next;
 }
}

void gnuplot(ponto* route)
{
 char saida[10]="saida.txt";
 int s;

 salve_file(route,saida);

 system("gnuplot tsp.gn");
 cout << "digite: ";
 cin >> s;

}

double create_route(ponto** route, ponto** P)
{

 double perc=0;
 ponto* Aux[3];
 *route=new ponto;
 (*route)->coord=(*P)->coord;
 (*route)->prev=*route;
 (*route)->next=*route;


 del(P,(*P)->coord);

 while(*P) {

  perc+=point_closer((*route), P, &Aux[0], &Aux[1]);

  Aux[2]=new ponto;
  Aux[2]->coord=Aux[1]->coord;
  Aux[2]->prev=Aux[0];
  Aux[2]->next=Aux[0]->next;
  Aux[0]->next->prev=Aux[2];
  Aux[0]->next=Aux[2];

  del(P,Aux[1]->coord);
 }

 return perc;
}

double tsp(ponto *R) {

 double d[3];
 d[2]=0;

 ponto *last=R;
 while(last->next) {
  ponto *closer[2]={NULL,NULL};

  d[1]=1e+30;
  for( ponto *i=last->next; i!=NULL; i=i->next) {
   for( ponto *j=R; j!=last; j=j->next) {

    d[0]=abs(j->coord-i->coord)+abs(i->coord-j->next->coord)-abs(j->coord-j->next->coord);

    if(d[0]<d[1]) {
     d[1]=d[0];
     closer[0]=i;
     closer[1]=j;
    }
   }

   d[0]=abs(last->coord-i->coord)+abs(i->coord-R->coord)-abs(last->coord-R->coord);

   if(d[0]<d[1]) {
    d[1]=d[0];
    closer[0]=i;
    closer[1]=last;
   }
  }

  d[2]+=d[1]; 

   if(closer[0]->next)
    closer[0]->next->prev=closer[0]->prev;
   closer[0]->prev->next=closer[0]->next;

   closer[0]->next=closer[1]->next;
   closer[0]->prev=closer[1];

   if(closer[1]->next) {
    closer[1]->next->prev=closer[0];
    closer[1]->next=closer[0];
   }
   if(closer[1]==last) last=last->next;
 }
 return d[2];
}
