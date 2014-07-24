#include <iostream>
#include <fstream>
#include <complex>
#include <cstdlib>
#include <unistd.h>
//#include <boost/tuple/tuple.hpp>
//#include <gnuplot-iostream.h>

using namespace std;

typedef struct Ponto {
  complex<double> coord;

  struct Ponto* next;
  struct Ponto* prev;
} ponto;

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


ponto* read_file_points(char* s) {

 ifstream data(s);

 if(!data) {
  cout << "Ascertain file " << s << endl;
  return NULL;
 }

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

// Ponto cujo
double point_closer(ponto* route, ponto **P, ponto **out, ponto** nov)
{

 ponto* Aux[3];
 double dist[2];

 Aux[0]=*P;
 dist[1]=1e+30;

 while(Aux[0]) {

  dist[0]=dist_route(route, Aux[0]->coord, &Aux[1]);

  if(dist[0]<0) {
/*
   Aux[2]=Aux[0]->next;
   del(P,Aux[0]->coord);
   Aux[0]=Aux[2];
*/
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

void salve_file(ponto* route, char* name_file)
{
 ponto* Aux;
 ofstream out(name_file);

 Aux=route;
 if(Aux==NULL) return;
 do {
  out  << Aux->coord.real() << " " << Aux->coord.imag() << endl;
  Aux=Aux->next;
 } while(Aux!=route);
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
/*
 Gnuplot gp;

 char saida[10]="saida.txt", entrada[10]="dados.txt";
 vector<boost::tuple<double, double> > data, ent;

 
 ifstream out(saida), in(entrada);

 gp << "set xrange [-1:10]; set yrange [-1:10]\n";
 gp << "set term gif animate\n";
 gp << "set output 'test.gif'\n";
 double aux[2];
 while(in >> aux[0] >> aux[1]) {
  ent.push_back(boost::make_tuple(aux[0],aux[1]));
 }
*/

 double perc=0;
 ponto* Aux[3];
 *route=new ponto;
 (*route)->coord=(*P)->coord;
 (*route)->prev=*route;
 (*route)->next=*route;
/*
 data.push_back(boost::make_tuple((*route)->coord.real(),(*route)->coord.imag()));
 gp << "plot '-' with linespoint ls 1\n";
 gp.send1d(data);
 gp << "plot '-' with points ls 2\n";
 gp.send1d(ent);
*/

 del(P,(*P)->coord);

 while(*P) {

  perc+=point_closer((*route), P, &Aux[0], &Aux[1]);
/*
  aux[0]=Aux[1]->coord.real();
  aux[1]=Aux[1]->coord.imag();

  data.push_back(boost::make_tuple(aux[0],aux[1]));
  gp << "plot '-' with linespoint ls 1\n";
  gp.send1d(data);
  gp << "plot '-' with points ls 2\n";
  gp.send1d(ent);
*/

  Aux[2]=new ponto;
  Aux[2]->coord=Aux[1]->coord;
  Aux[2]->prev=Aux[0];
  Aux[2]->next=Aux[0]->next;
  Aux[0]->next->prev=Aux[2];
  Aux[0]->next=Aux[2];

  del(P,Aux[1]->coord);
 }
// gp << "set output\n";

 return perc;
}
