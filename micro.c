#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

//
// This file is written to C99 or better
//

#ifndef clock_gettime
// we are probably in Mach.
#include <mach/mach_time.h>

mach_timebase_info_data_t g_timebase;
void clock_init() {
  mach_timebase_info(&g_timebase);
  printf("timebase numer is %d\n",g_timebase.numer);
  printf("timebase denom is %d\n",g_timebase.denom);
}

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 0
int clock_gettime(int clk_id, struct timespec *t){
    uint64_t abs_t;
    abs_t = mach_absolute_time();
    double nseconds = ((double)abs_t * (double)g_timebase.numer)/((double)g_timebase.denom);
    double seconds = ((double)abs_t * (double)g_timebase.numer)/((double)g_timebase.denom * 1e9);
    t->tv_sec = seconds;
    t->tv_nsec = nseconds;
    return 0;
}
#endif 
// defininig clock_gettime in Mach


// Raw is cool, but it's about 4 years old.
// Allow use on older & more standard C implementations
#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
#endif

// returns milliseconds in floating point
//

double diff_time(struct timespec *start, struct timespec *end ) {
  int secs = end->tv_sec - start->tv_sec;
  int nano = end->tv_nsec - start->tv_nsec; // this could be negative, stay unsigned
  double result = (double) secs + (double) nano;
  result *= 1000.0; // milliseconds
  return(result);
}



void f1()
{
  struct timespec start, end;

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);

	int x = 10;
	for (int i = 0; i < 100000; i++) {
		x = ( 2 * x ) + x + 1;
  }

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  printf("f1 took %f milliseconds\n",diff_time(&start,&end));

}

// How do you catenate in C? Write a quick function, of course !
// this function allocates memory that must be freed by the caller

char *str_cat(int nargs, ...) {

  va_list ap;

  int len = 0;

  // count the len, hope the CPU cache is good
  va_start(ap, nargs);
  for (int i =0 ; i < nargs ; i++ ) {
    len += strlen( va_arg(ap, char *) );
  }
  va_end(ap);

  // fetch me some memory
  char *s = malloc(len + 1);
  char *sp = s;

  va_start(ap, nargs);
  for (int i =0 ; i < nargs ; i++ ) {
    char *c = va_arg(ap, char *);
    int l = strlen(c);
    memcpy(sp, c, l);
    sp += l;
  }
  va_end(ap);
  *sp = 0;

  return(s);
}

// Just get the lengths

int str_cat_len(int nargs, ...) {

  va_list ap;

  int len = 0;

  // count the len, hope the CPU cache is good
  va_start(ap, nargs);
  for (int i =0 ; i < nargs ; i++ ) {
    len += strlen( va_arg(ap, char *) );
  }
  va_end(ap);

  return(len);
}

// copy into an allocated buffer

char * str_cat_cpy(int nargs, char *s, ...) {
  va_list ap;

  va_start(ap, s);
  for (int i =0 ; i < nargs ; i++ ) {
    char *c = va_arg(ap, char *);
    int l = strlen(c);
    memcpy(s, c, l);
    s += l;
  }
  va_end(ap);
  s = 0;
  s++;

  return(s);
}

void f2()
{
  struct timespec t0;
  clock_gettime(CLOCK_MONOTONIC_RAW, &t0);

  int nStrings = 1000;
  int nCats = 100000;

  char * a1[nStrings]; // stack allocation for pointers that we alloca
  char c = 'a';
  a1[0] = alloca(2);
  a1[0][0] = c;
  a1[0][1] = 0;

  // This uses about 0.5MB on the stack

  for (int i=1;i<nStrings;i++) {
    if (c == 0) c++;
    a1[i] = alloca(i+2);
    memcpy(a1[i], a1[i-1], i);
    a1[i][i] = c;
    a1[i][i+1] = 0;
    c++;
  }

  // What's the best way to catenate in C ?
  // write your own cat function, of course!

  struct timespec t1;
  clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

  char *a2[nCats];

  for (int i = 0; i < nCats ; i++) {
    a2[i] = str_cat( 7, a1[i % sizeof(a1)], 
                        a1[(i+7)%sizeof(a1)], 
                        a1[(i+17)%sizeof(a1)], 
                        a1[(i+27)%sizeof(a1)], 
                        a1[(i+37)%sizeof(a1)], 
                        a1[(i+47)%sizeof(a1)], 
                        a1[(i+57)%sizeof(a1)]
                    );
  }

  // gotta free everything explicitly! We're in C land!
  for (int i = 0; i < nCats ; i++) {
    free(a2[i]);
  }

  struct timespec t2;
  clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

  // stack too small for this but can do one big malloc Might blow up.

  char *a3[nCats];

  int totlen = 0;
  for (int i = 0; i < nCats ; i++) {
    totlen += str_cat_len( 7, a1[i % sizeof(a1)], 
                              a1[(i+7)%sizeof(a1)], 
                              a1[(i+17)%sizeof(a1)], 
                              a1[(i+27)%sizeof(a1)], 
                              a1[(i+37)%sizeof(a1)], 
                              a1[(i+47)%sizeof(a1)], 
                              a1[(i+57)%sizeof(a1)] );
  }

  char *buf, *b = malloc(totlen);

  int i=0;
  for (int i = 0 ; i < nCats-1 ; i++) {
    a3[i] = b;
    b = str_cat_cpy( 7, b, a1[i % sizeof(a1)], 
                                a1[(i+7)%sizeof(a1)], 
                                a1[(i+17)%sizeof(a1)], 
                                a1[(i+27)%sizeof(a1)], 
                                a1[(i+37)%sizeof(a1)], 
                                a1[(i+47)%sizeof(a1)], 
                                a1[(i+57)%sizeof(a1)] );
  }

  free(buf);

  struct timespec t3;
  clock_gettime(CLOCK_MONOTONIC_RAW, &t3);

  printf("f2 creatstr %f ms, cat with malloc %f, cat on stack %f\n",diff_time(&t0,&t1),diff_time(&t1,&t2),diff_time(&t2,&t3));

}

// not sure how best to represent a map
#if 0

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

#endif

int main(){

  printf( "C performance test\n" );
  f1();
  f2();
  // f5();
  printf( "end C performance test\n" );
}