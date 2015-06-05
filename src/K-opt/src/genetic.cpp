#include <k-opt.hpp>


int main(int argc, char** argv) {

 route R=read_route(argv[1]);
/*
 std::vector<route> Aux(genetic_opt2(&R)); 

 uint n=R.size();
 for ( uint i=0; i<n; i++) {
	std::stringstream out;
	save_route(Aux[i],out.str().c_str());
 }
*/
 route Aux(simple_step(R));
 save_route(Aux,argv[2]); 

 return 0;
}
