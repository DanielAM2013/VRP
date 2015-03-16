#include "../../lib/madj.hpp"

int main()
{
 char file[]="points.dat";
 vector<point> R=read(file);

// for( num i=0; i<R.size(); i++) 
//  cout << R[i];
// cout << endl;

 madj A;
 A.geometric(R);


// A.insert_arc(0,1);
// cout << A.in_degree(0)  << " " << A.out_degree(0) << endl;
 
 A.print(0);

 return 0;
}


