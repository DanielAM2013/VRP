#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

typedef cl_double2 point;
typedef std::vector<point> route;

std::ostream& operator<< ( std::ostream &out, const point& P)
// Body
{
 out << "(" << P.s0 << "," << P.s1 << ")";
 return out;
}



cl_double2 operator+ ( const cl_double2& first, const
cl_double2& second) {

 cl_double2 aux;
 aux.s0=first.s0+second.s0;
 aux.s1=first.s1+second.s1;

 return aux;
}

point operator/ ( const point& num, const double& dem) {

 point aux;
 aux.s0=num.s0/dem;
 aux.s1=num.s1/dem;

 return aux;
}

bool operator!= ( const point& A, const point& B) {
 return ((A.s0 != B.s0) || (A.s1 != B.s1));
}

/*
std::istream& operator>> ( std::istream &in, const point& P)
// Body
{
// in.ignore();
 in >> P.s0 ;
 in.ignore();
 in >> P.s1;
// in.ignore();

 return in;
}
*/
route read_route ( char* file )
{

	std::ifstream points ( file, std::ios::in );

	route Aux;
	point aux;
	while ( points >> aux.s0 >> aux.s1 ) {
		Aux.push_back(aux);
	}

	return Aux;
}
