#include "tsp.h"

int main()
{
 // read_file_points
 ponto* test;
 char in[10]="dados.txt";
 
 test=read_file_points(in);
 print_list_simple(test);

 // print_point
 ponto* route=new ponto;
 route->coord=test->coord;

 route->next=route;
 route->prev=route; 

 ponto *Aux[3];

/*
 cout << dist_route(route,test->next->coord, &Aux[0]);

 print_point(Aux[0]->coord);

 print_list_duple(route);

 del(&route,test->coord);

 cout << route << endl;

 del(&test, test->next->coord);

 print_list_simple(test);
*/

 int i;
/*
// Aux[0]=test;
// for(i=0; i<7; i++)
 while(test) 
 {
  cout << point_closer(route, &test, &Aux[0], &Aux[1]) << endl;

//  cout << dist_route(route, Aux[0]->coord, &Aux[1]);

//  print_list_duple(route);
//  print_point(Aux[0]->coord);
//  print_point(Aux[1]->coord);

  del(&test, Aux[1]->coord);

  cout << endl;

  print_list_simple(test);
//  Aux[0]=Aux[0]->next;
 }
*/

 route=NULL;
 cout << create_route(&route, &test) << endl;

// cout << test << endl;

// print_list_duple(route);
  print_list_duple(route);



 










 return 0;
}
