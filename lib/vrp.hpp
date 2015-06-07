#include <route.hpp>
#include <algorithm>
#include <sstream>

void print_train(train T) 
{
 std::cout << "---------------------------------------" << std::endl;
 for( train::iterator i=T.begin(); i!=T.end(); i++) {
  for( route::iterator j=i->begin(); j!=i->end(); j++)
   std::cout << *j << " ";
  std::cout << std::endl;
 }
}

void save_train( train T, char* filename) {
 unsigned int k=0;
 std::stringstream s;
 s << filename;
 std::ofstream  out(s.str().c_str());

 for( train::iterator i=T.begin(); i!=T.end(); i++) {

  for( route::iterator j=i->begin(); j!=i->end(); j++)
   out << j->real() << " " << j->imag() << std::endl;

  out << (i->begin())->real() << " " << (i->begin())->imag() <<  std::endl
	  << std::endl;
 }
 out.close();
}

double cust_train( train X, double k) {

 double aux=0;
 for( int i=0; i<X.size(); i++) 
  aux+=cust_route(X[i]); 

 return aux;
}


double cust_heuristic( train X, double k) {
 double aux=0;

 for( int i=0; i<X.size(); i++) 
  aux+=pow(cust_route(X[i]),k); 

 return aux;
}

double nearest_neighbor2(route *R) {
 double d[3];
 d[2]=0;

 route::iterator closer[2];

 for( route::iterator last=R->begin(); last+1!=R->end(); last++) {
  d[1]=1e+30;
  for( route::iterator i=last+1; i!=R->end(); i++) {
   for( route::iterator j=R->begin(); j!=last; j++) {

    d[0]=std::abs(*j-*i)+std::abs(*i-*(j+1))-std::abs(*j-*(j+1));
    if(d[0]<d[1]) {
     d[1]=d[0];
     closer[0]=i;
     closer[1]=j;
    }
   }

   d[0]=std::abs(*last-*i)+std::abs(*i-*R->begin())-std::abs(*last-*R->begin());
   if(d[0]<d[1]) {
    d[1]=d[0];
    closer[0]=i;
    closer[1]=last;
   }
  }

  d[2]+=d[1];

  point aux=*closer[0];
  R->erase(closer[0]);
  R->insert(closer[1]+1, aux);
 }
 return d[2];
}

double clarke_wright_tsp ( route* first, train* second, double (*TSP)(route*), double (*CUST)( train, double))
{

 int N=first->size();
 double Power=2;
 point aux=(*first)[0];

 //! Sort
 //! sort points in counterclockwise mode with initial point like origin
 for( route::iterator i=first->begin(); i!=first->end(); i++) {
  *i-=aux;
 }

 std::sort(first->begin()+1, first->end(), operator<);

 for( route::iterator i=first->begin(); i!=first->end(); i++) {
  *i+=aux;
 }
 //! endSort

 //! Aloc 
 // aloc one point by route
 for( int i=1; i<N; i++) {
  route aux;
  aux.push_back((*first)[0]);
  aux.push_back((*first)[i]);
  second->push_back(aux);
  aux.clear();
 }
 //! endAloc
 //
 double d[3]={0,0,(*CUST)(*second,Power)};

 train Aux, Aux1(*second);

 //! Check
 // check all linear possibilities of merge adjacents routes
 for ( int k=0; k<N-1; k++)
 {
  d[2]=d[1];
  // Train copy
  Aux=train(*second);
  *second=train(Aux1);
  d[1]=(*CUST)(Aux, Power);

  //! Merge_and_Analysis
  // merge adjacent routes and check if cust is less of last
  // Begin -> End-1
  for( train::iterator i=Aux.begin(); i+1!=Aux.end(); i++) {
   //! Add_Route
   // add next route in end of current route after first element( origin) and
   // erase next route of this copy
   i->insert(i->end(), (i+1)->begin()+1, (i+1)->end());
   Aux.erase(i+1);
   // End Add_Route
   // ! Tsp
   (*TSP)(&*i);
   // End Tsp
   // ! Analysis
   // Check of this modificed copy have cust less of last copy
   d[0]=(*CUST)(Aux,Power);
   if(d[0]<d[1]) {
    d[1]=d[0];
    Aux1=train(Aux);
   }
   // End Analysis
   // Restore original copy
   Aux=train(*second);
  }
  
  Aux=train(*second);
  
  (Aux.end()-1)->insert((Aux.end()-1)->end(), (Aux.begin())->begin(), (Aux.begin())->end());

  (*TSP)(&*(Aux.end()-1));
  Aux.erase(Aux.begin());
  d[0]=(*CUST)(Aux,Power);
  if(d[0]<d[1]) {
   d[1]=d[0];
   Aux1=train(Aux);
  }
  // End Merge_and_Analysis
 }

 return (*CUST)(*second,Power);
}
