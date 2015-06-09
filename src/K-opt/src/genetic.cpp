#include <train.hpp>
#include <k-opt.hpp>


int main(int argc, char** argv) {

 route R=read_route(argv[1]);

 route Aux(genetic_opt2(R)); 

 std::cout << cust_route(R)-cust_route(Aux) << std::endl;

 save_route(Aux,argv[2]);

 return 0;
}
