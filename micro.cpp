#include <iostream>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <map>

using namespace std;

void f1()
{
	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	int x = 10;
	for (int i = 0; i < 100000; i++) {
		x = ( 2 * x ) + x + 1;
  }

  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  chrono::duration<double> time_span = chrono::duration_cast < chrono::duration<double> > (end - start);
  std::cout << "f1 took " << time_span.count() << " seconds. " << std::endl;
}

void f2()
{
  chrono::steady_clock::time_point t0 = chrono::steady_clock::now();

  int nStrings = 1000;
  int nCats = 100000;

  std::vector<std::string> a1(nStrings);
  char c = 'a';
  std::string myStr(&c);
  a1[0] = myStr;

  for (int i=1;i<nStrings;i++) {
    if (c == 0) c++;
    a1[i] = a1[i-1] + c;
    c++;
  }

  // Do the vector work with push, like many languages do

  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

  vector<string> a2;
  for (int i = 0; i < nCats ; i++) {
    a2.push_back( a1[i % a1.size()] + a1[(i+7)%a1.size()] + a1[(i+17)%a1.size()] + 
      a1[(i+27)%a1.size()] + a1[(i+37)%a1.size()] + a1[(i+47)%a1.size()] + a1[(i+57)%a1.size()] );
  }

  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

  // do the vector work with a preallocated array, as is the common thing in C
  vector<string> a3(nCats);
  for (int i = 0; i < nCats ; i++) {
    a3[i] = a1[i % a1.size()] + a1[(i+7)%a1.size()] + a1[(i+17)%a1.size()] + 
      a1[(i+27)%a1.size()] + a1[(i+37)%a1.size()] + a1[(i+47)%a1.size()] + a1[(i+57)%a1.size()] ;
  }

  chrono::steady_clock::time_point t3 = chrono::steady_clock::now();

  std::cout << "f2 createstr " 
            << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() 
            << " sec , plus cat " 
            << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
            << std::endl ; 
}

void f5()
{
  chrono::steady_clock::time_point t0 = chrono::steady_clock::now();

  for (int i = 0; i < 1000000;i++) {
    map<int, string> a;
    for (int j = 0; j < 50; j++) {
      a[j] = to_string(j);
    }
  }

  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

  std::cout << "f5 milliseconds " 
            << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() 
            << std::endl ;

}

int main(){

  printf( "quick performance test\n" );
  f1();
  f2();
  f5();
  std::cout << "end quick performance test\n";
}