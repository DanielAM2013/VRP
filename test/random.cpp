// normal_distribution
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main()
{
 int N;
 char saida[10]="dados.txt";
 cout << "digite n: ";
 cin >> N;

 ofstream output(saida);

 default_random_engine generator;
 normal_distribution<double> distribution(5.0,2.0);

 for (int i=0; i<N; ++i) {
   double real = distribution(generator);
   double imag = distribution(generator);

   output << real << " " << imag << endl;
 }

  return 0;
}
