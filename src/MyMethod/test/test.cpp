#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <cstring>

int main()
{
 

 for( int k=0; k!=10; k++) {
  std::stringstream s;
  s << k << ".test";
// char inteiro=(char) k;
// std::string

  std::ofstream ofs (s.str().c_str());

   ofs << k;

  ofs.close();
 }

 return 0;
}
