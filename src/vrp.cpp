#include "tsp.h"
#include <new>

// Adicionar class rota
// Grafo 
class point
{
 private:
 std::complex<double> coord;
 public:

 point (double x=0, double y=0) {
  coord.real(x);
  coord.imag(y);
 }

 void set(double x, double y) {
   coord.real(x);
   coord.imag(y);
 }

 std::complex<double> Coord(void) {
  return coord;
 }

 bool operator==(point P) {
  return (coord==P.Coord());
 }

 void print(void) {
  std::cout << coord;
 }
};

// doble liked list
class route
{
 private:
 point p;
 route* next;
 route* prev;

 public:
// Constructor
/*
 route(double x, double y, route* R) {
  p(x,y);
  next=R->next;
  prev=R;
 }
*/
 route(double x, double y) {
  p.set(x,y);
  next=prev=this;
 }

/*
 void set(double x, double y, route* R) {
  p.set(x,y);
  next=R->Next;
  prev=R;
 }
*/
// Return 
 route* Next(void) {
   return next;
 }

 route* Prev(void) {
  return prev;
 }

 point P(void) {
  return p;
 }

 void display(void) {
  p.print();
 }

// Read
 void print(void) {
  route* aux=this;

  if(aux!=NULL)
  do {
   aux->display();
   aux=aux->Next();
  } while(aux->next!=aux);
 }

// Struct
 route* search_point(point P){
  route* aux=this;

  if(aux!=NULL)
  do {
   if(P==aux->P()) return aux;
   aux=aux->Next();
  } while(aux->Next!=aux);
 }

 void insert_point_next(point P) {
  route aux[2];
  aux[0]=new route;
  aux[0]->set(P);

  aux[1]=this;
  // Pesquisar ponto com ângulo menor
  while(aux[1]) {
   
  }
 }

// Algoritm

};

int main()
{
 point p(1.0,2.0);

// p.print(); 
// std::cout << std::endl;

 route r(1.2,1.0);
 r.display();

 return 0;
}

