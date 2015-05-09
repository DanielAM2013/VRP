#include <vrp.hpp>
#include <sstream>

route read_file(char file[]) {

 std::ifstream data(file, std::ifstream::in);
 
 route first;
 point aux;

 while( data >> aux.real() >> aux.imag()) {
  first.push_back(aux);
 }

 return first;
}

void print_train(train T) 
{
 std::cout << "---------------------------------------" << std::endl;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
}

void save_train( train T, char* filename) {
 unsigned int k=0;
 std::stringstream s;
 s << filename;
 std::ofstream  out(s.str().c_str());

 for( train::iterator i=T.begin(); i!=T.end(); i++) {

  for( route::iterator j=i->begin(); j!=i->end(); j++)
   out << j->real() << " " << j->imag() << std::endl;

  out << (i->begin())->real() << " " << (i->begin())->imag() <<  std::endl
	  << std::endl;
 }
 out.close();
}


int main( int argc, char** argv)
{
 // Ler Arquivo
 route first=read_file(argv[1]); 

 int N=first.size();

 point aux=*first.begin();

 // Ordenar
 for( route::iterator i=first.begin(); i!=first.end(); i++) {
  *i-=aux;
 }

 std::sort(first.begin()+1, first.end(), operator<);

 for( route::iterator i=first.begin(); i!=first.end(); i++) {
  *i+=aux;
 }

// Alocar
 train second;
 for( int i=1; i<N; i++) {
  route aux;
  aux.push_back(first[0]);
  aux.push_back(first[i]);
  second.push_back(aux);
  aux.clear();
 }

 double d[3]={0,0,cust(second)};

 train Aux, Aux1(second);

 for ( int k=0; k<N-1; k++)
 {
  d[2]=d[1];
  Aux=train(second);
  second=train(Aux1);
  d[1]=cust(Aux);
  for( train::iterator i=Aux.begin(); i+1!=Aux.end(); i++) {
   // Mesclar roca com a seguinte numa variável auxiliar
   i->insert(i->end(), (i+1)->begin()+1, (i+1)->end());
   // Aplicar o tsp
   tsp(&*i);
   // Inserir rotas mescladas no train Aux
   Aux.erase(i+1);
   // Avaliar roteamento
   d[0]=cust(Aux);
   // Ordenar custo
   if(d[0]<d[1]) {
    d[1]=d[0];
    Aux1=train(Aux);
   }
   Aux=train(second);
  }

  Aux=train(second);
  
  (Aux.end()-1)->insert((Aux.end()-1)->end(), (Aux.begin())->begin(), (Aux.begin())->end());

  tsp(&*(Aux.end()-1));
  // Inserir rotas mescladas no train Aux
  Aux.erase(Aux.begin());
  // Avaliar roteamento
  d[0]=cust(Aux);
 // Ordenar custo
  if(d[0]<d[1]) {
   d[1]=d[0];
   Aux1=train(Aux);
  }
 }
 save_train(second,argv[2]);
 std::cout << cust(second) << std::endl;

 return 0;
}
