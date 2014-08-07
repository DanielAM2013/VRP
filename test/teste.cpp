// Abrir arquivo saida.txt e plotar os pontos com gnuplot
#include <iostream>
#include <fstream>
#include <complex>
#include <cstdlib>

using namespace std;

typedef struct Ponto {
  complex<double> coord;

  struct Ponto* next;
  struct Ponto* prev;
} ponto;

// Ler arquivo e retornar ponteiro para lista encadeada que o contem
ponto* read_file_pontos(char* s) {

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

int main()
{
 char dados[10]="dados.txt";

 ponto* route=read_file_pontos(dados);

 system("gnuplot -c"



 return 0;
}








