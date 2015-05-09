#include <convexo.hpp>

int main(int argc, char** argv)
{
 route X=read(argv[1]);
 route Aux=bordo_convexo(X);
 write(Aux,argv[2]);

 return 0;
}
