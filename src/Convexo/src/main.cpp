#include <convexo.hpp>

int main(int argc, char** argv)
{
 route X=read_route(argv[1]);
 route Aux=bordo_convexo(X);
 std::cout << Aux.size() << std::endl;
 save_route(Aux,argv[2]);

 return 0;
}
