#include "lib/vrp.hpp"
#include <sstream>

void print_train(train T) 
{
 std::cout << "---------------------------------------" << std::endl;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
}

void save_fleet( train T) {
 unsigned int k=0;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  std::stringstream s;
  s << k << ".test";
  std::ofstream  out(s.str().c_str());

  for( route::iterator j=i->begin(); j!=i->end(); j++)
   out << j->real() << " " << j->imag() << std::endl;
  out.close();
  k++;
 }
}
