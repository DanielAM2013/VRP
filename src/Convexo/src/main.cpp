#include <convexo.hpp>

int main(int argc, char** argv)
{
 route X=read_route(argv[1]);
 route Aux=bordo_convexo(X);
 save_route(Aux,argv[2]);

 return 0;
}
