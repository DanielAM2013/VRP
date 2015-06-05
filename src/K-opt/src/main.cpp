#include <k-opt.hpp>

int main( int argc, char* argv[]){
 
 route R=read_route(argv[1]);
 for( int k=0; k<6; k++)
  opt2(&R);

 save_route(R,argv[2]);
 std::cout << cust_route(R) << std::endl;
 
 return 0;
}
