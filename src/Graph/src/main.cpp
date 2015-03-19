int main()
{
// grafo X(5);
 char file[]="points.dat";
 grafo X(file);

// vector<bool> mark(X.size());

 X.insert(3,7);
 cout << X.in_loop(3, 3, 3, mark) << endl;
 X.insert(0,3);
 cout << X.in_loop(0, 0, 0, mark) << endl;
 X.insert(0,7);

// cout << X.enu(X.node(15)) << " " << X.node(15) << endl;

// X.KRUSKAL(); 
// X.CHRISTOFIDES();
// for( num k=0; k<X.size(); k++) {
//  if(X.in_loop(k, k, k, mark)) cout << k << endl;
// }

 char out[]="output.dat";
 X.save(out);

// X.print(0);
// X.insert(5,9);
//  cout << X.getw(1,3) << endl;
//  X.print(0);
// for( num k=0; k<X.size(); k++)
//  if( X.degre(k)%2==1)
//   cout << X.degre(k) << endl;


// using namespace boost::numeric::ublas;
//    matrix<double> m (3, 3);
//    for (unsigned i = 0; i < m.size1 (); ++ i)
//        for (unsigned j = 0; j < m.size2 (); ++ j)
//            m (i, j) = 3 * i + j;
//    std::cout << m << std::endl;
// system("gnuplot -p -e "
 return 0;
}
