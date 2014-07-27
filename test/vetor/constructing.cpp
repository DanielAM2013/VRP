// constructing vectors
#include <iostream>
#include <vector>
#include <complex>

int main ()
{
  unsigned int i;

  // constructors used in the same order as described above:
  std::vector<int> first;                                // empty vector of ints
  std::vector<int> second (4,100);                       // four ints with value 100
  std::vector<int> third (second.begin(),second.end());  // iterating through second
  std::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  // Teste with complex
  std::vector<std::complex<double> > coord;
  coord.a
 // std::complex<double> test(1.0,1.0);
 std::vector<std::complex<double> >::iterator t = coord.begin();

 std::cout << *t <<  std::endl;



  std::cout << "The contents of fifth are:";
  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
