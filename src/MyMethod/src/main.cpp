#include <vrp.hpp>
#include <k-opt.hpp>

int main( int argc, char** argv)
{
 route first=read_route(argv[1]); 
 route aux(first);
 train second;
 std::cout << clarke_wright_tsp(&aux,&second, nearest_neighbor2, cust_train) << std::endl;
 save_train(second,argv[2]);
 return 0;
}
