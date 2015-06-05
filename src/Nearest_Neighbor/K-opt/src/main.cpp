#include <k-opt.hpp>

int main( int argv, char* argc[]){
 
 route R=read_route(argc[1]);
 for( int k=0; k<6; k++)
  opt2(&R);

 save_route(R,argc[2]);
 std::cout << cust_route(R) << std::endl;
 
 return 0;
}
