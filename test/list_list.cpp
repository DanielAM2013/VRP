#include <iostream>
#include <list>
#include <new>
#include <complex>

int main()
{
 typedef std::list<int> Inteiro;
 typedef std::list<Inteiro> Lista_Inteiros;

 Inteiro test;
 Lista_Inteiros Test;


 test.push_back(10);
 test.push_back(11);

 Test.push_back(test);

 Lista_Inteiros::iterator I=Test.begin();

 std::cout << *(++I->begin()) << std::endl;


 for(Inteiro::iterator i=test.begin(); i!=test.end(); ++i)
  std::cout << *i << std::endl;


 return 0;
}
