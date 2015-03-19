#include "../lib/train.hpp"

double nn( route *R, train *T) {

 // Alocar
 for( int i=1; i<N; i++) {
  route aux;
  aux.push_back(first[0]);
  aux.push_back(first[i]);
  T->push_back(aux);
  aux.clear();
 }

 double d[3]={0,0,cust(*T)};

 train Aux[2];
 Aux[0]=train(*T);

 // Com no máximo poderá haver N mesclagens
 // Não é necessário mais verificações
 for( int k=0; k<N; k++)
 {
  d[2]=d[1];
  d[1]=cust(Aux[0]);

  for( train::iterator i=Aux.begin(); next(i)!=Aux.end(); i++) {

   // adicionar pontos de uma rota com a posterior em "i"
   i->insert(i->end(), (next(i))->begin()+1, (next(i))->end());

   // Aplicar o tsp a "i"
   tsp(&*i);

   // Remover segunda rota mesclada no train "Aux"
   Aux.erase(next(i));

   // Determinar custo da rota criada
   d[0]=cust(Aux[0]);

   // Verificar se há melhoramento de custo
   if(d[0]<d[1]) {
    d[1]=d[0];
    // Salvar rota com melhoramento
    Aux[1]=train(Aux[0]);
   }
   // Reinicializar variável "Aux" com "T
   Aux[0]=train(*T);
  }

 // Executar algoritmo para último elemento seguido do primeiro
  // adicionar primeiro elemento a rota do último
  (Aux[0].end()-1)->insert((Aux[0].end()-1)->end(), (Aux[0].begin())->begin(), (Aux[0].begin())->end());

  // Aplicar o TSP ao último elemento de "Aux"
  tsp(&*(Aux[0].end()-1));

  // Remover primeira rota de "Aux"
  Aux[0].erase(Aux[0].begin());

  // Determinar o custo da rota criada
  d[0]=cust(Aux[0]);

 // Verificar se há melhoramento de custo
  if(d[0]<d[1]) {
   d[1]=d[0];
   Aux[1]=train(Aux[0]);
  }
  // Retirar elementos de T
  T->clean();
  // Preencher com os elementos de "Aux[1]"
  *T=Aux[1];
 }
}


int main()
{
/*
// Ler Arquivo
 char test[]="points.dat";
 route first=read_file(test); 

 int N=first.size();


 for( route::iterator i=first.begin(); i!=first.end(); i++)
  std::cout << *i << std::endl;

 std::cout << tsp(&first) << std::endl;

 for( route::iterator i=first.begin(); i!=first.end(); i++)
  std::cout << *i << std::endl;
*/
/*
 point aux=*first.begin();

 for( route::iterator i=first.begin(); i!=first.end(); i++) {
  *i-=aux;
 }
// Ordenar
 std::sort(first.begin()+1, first.end(), operator<);

 for( route::iterator i=first.begin(); i!=first.end(); i++) {
  *i+=aux;
 }

 save_train(second);
 std::cout << cust(second) << std::endl;
*/
 return 0;
}
