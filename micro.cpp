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

  std::cout << "f1 took " 
            << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
            << " milliseconds. " << std::endl;
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

  std::cout << "f2 createstr only " 
            << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() 
            << " millisec , plus catenating " 
            << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
            << " millisec, optimzied vectors "
            << chrono::duration_cast<chrono::milliseconds>(t3 - t2).count()
            << std::endl ; 
}

void f5()
{
  chrono::steady_clock::time_point t0 = chrono::steady_clock::now();

  // the basic and most idomatic way to fulfill this
  for (int i = 0; i < 1000000;i++) {
    map<int, string> a;
    for (int j = 0; j < 50; j++) {
      a[j] = to_string(j);
    }
  }
  // NB: don't have to delete things. These are on the stack?

  chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

  // try with just one, and clearing it
  map<int, string> a1;
  for (int i = 0; i < 1000000;i++) {
    for (int j = 0; j < 50; j++) {
      a1[j] = to_string(j);
    }
    a1.clear();
  }

  chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

  // Re-use the same string --- is it the string create which is long?
  map<int, const char *> a2;
  for (int i = 0; i < 1000000;i++) {
    for (int j = 0; j < 50; j++) {
      a2[j] = "123";
    }
    a2.clear();
  }

  chrono::steady_clock::time_point t3 = chrono::steady_clock::now();


  std::cout << "f5 " 
            << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() 
            << " ms standard, "
            << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() 
            << " ms reusing map, "
            << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() 
            << " ms constant string "
            << std::endl ;

}

int main(){

  printf( "quick performance test\n" );
  f1();
  f2();
  f5();
  std::cout << "end quick performance test\n";
}