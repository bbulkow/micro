package main

import "time"
import "strconv"
import "fmt"
import "math/big"
import "sync"

func f1() {

  t0 := time.Now()

  var x int = 10

  for i := 0; i < 1000000; i++ {
       x = ( 2 * x ) + x + 1
   }

   t1 := time.Now()

   var x_b *big.Int = big.NewInt(10)
   var one *big.Int = big.NewInt(1)
   var two *big.Int = big.NewInt(2)

   for i:=0; i < 100000; i++ {
      x2_b := big.NewInt(0).Add( one, x_b );
      x3_b := big.NewInt(0).Mul( two, x_b );
      x_b.Add(x2_b, x3_b);
    }

   t2 := time.Now()

   //fmt.Printf("t1: answer %v\n time1 %v time2 %v\n", x_b, t1.Sub(t0), t2.Sub(t1) );
   fmt.Printf("t1: time1 %v time2 %v\n", t1.Sub(t0), t2.Sub(t1) );
} 

func f5() {
	t0 := time.Now()

   for x := 0; x < 1000000; x++ {
       a := make(map[int] string);
       for a1 := 0; a1 < 50; a1++ {
           a[a1] = strconv.Itoa(a1);
       }
   }
   duration := time.Now().Sub(t0)

   fmt.Printf("t5: time consumed %v\n",duration );
} 


func f5a() {
  t0 := time.Now()

   for x := 0; x < 1000000; x++ {
       a := make(map[int] string, 50);
       for a1 := 0; a1 < 50; a1++ {
           a[a1] = strconv.Itoa(a1);
       }
   }
   duration := time.Now().Sub(t0)

   fmt.Printf("t5: tuned array %v\n",duration );
} 

func f5b() {
  t0 := time.Now()

   for x := 0; x < 1000000; x++ {
       a := make(map[int] string, 50);
       for a1 := 0; a1 < 50; a1++ {
           a[a1] = "123456";
       }
   }
   duration := time.Now().Sub(t0)

   fmt.Printf("t5: tuned array no string %v\n",duration );
} 

func f5c() {
  t0 := time.Now()

  a := make(map[int] string, 50);
   for x := 0; x < 1000000; x++ {
       // a := make(map[int] string, 50);
       for a1 := 0; a1 < 50; a1++ {
           a[a1] = "123456";
       }
   }
   duration := time.Now().Sub(t0)

   fmt.Printf("t5: one array, tuned array, no string %v\n",duration );
} 

// Microbenchmark: rw mutexes vs standard mutexes
//

func f6() {

  var mutex = &sync.Mutex{}

  var rw_mutex = &sync.RWMutex{}

  i := 0

  t0 := time.Now()

  state := make(map[int]int)

  for r := 0 ; r < 100000 ; r++ {
    i++
    state[i] = i
  }

  t1 := time.Now()

  state = make(map[int]int)

  for r := 0 ; r < 100000 ; r++ {
    mutex.Lock()
    i++
    state[i] = i
    mutex.Unlock()
  }

  t2 := time.Now()

  state = make(map[int]int)

  for r := 0 ; r < 100000 ; r++ {
    rw_mutex.Lock()
    i++
    state[i] = i
    rw_mutex.Unlock()
  }

  t3 := time.Now()

  state = make(map[int]int)

  for r := 0 ; r < 100000 ; r++ {
    rw_mutex.RLock()
    i++
    state[i] = i
    rw_mutex.RUnlock()
  }

  t4 := time.Now()

 fmt.Printf("t6: without mutex %v with mutex %v with rw %v with rw R %v\n",
    t1.Sub(t0),t2.Sub(t1),t3.Sub(t2),t4.Sub(t3));

}

type hits struct {
  sync.Mutex
  n int
}

func f6a_2(counter *hits, wg *sync.WaitGroup) {

  for j:=0;j< 1000000; j++ {

    counter.Lock()
    counter.n++
    counter.Unlock()

    y := 0
    for i:=0;i<100;i++ {
      y += (i * 2) + i
    }
  }
  wg.Done()
}

func f6a() {

  var h hits
  var wg sync.WaitGroup

  wg.Add(4)

  t0 := time.Now()

  for i := 0;i < 4; i++ {
    go f6a_2(&h, &wg)
  }

  wg.Wait()

  t1 := time.Now()

 fmt.Printf("t6a:  %v\n",
    t1.Sub(t0));

}

type hits_b struct {
  sync.RWMutex
  n int
}

func f6b_2(counter *hits_b, wg *sync.WaitGroup) {

  for j:=0;j< 1000000; j++ {

    counter.Lock()
    counter.n++
    counter.Unlock()

    y := 0
    for i:=0;i<100;i++ {
      y += (i * 2) + i
    }
  }
  wg.Done()
}

func f6b() {

  var h hits_b
  var wg sync.WaitGroup

  wg.Add(4)

  t0 := time.Now()

  for i := 0;i < 4; i++ {
    go f6b_2(&h, &wg)
  }

  wg.Wait()

  t1 := time.Now()

 fmt.Printf("t6b:  %v\n",
    t1.Sub(t0));

}

func f6c_2(counter *hits_b, wg *sync.WaitGroup) {

  for j:=0;j< 1000000; j++ {

    counter.RLock()
    counter.n++
    counter.RUnlock()

    y := 0
    for i:=0;i<100;i++ {
      y += (i * 2) + i
    }
  }
  wg.Done()
}

func f6c() {

  var h hits_b
  var wg sync.WaitGroup

  wg.Add(4)

  t0 := time.Now()

  for i := 0;i < 4; i++ {
    go f6c_2(&h, &wg)
  }

  wg.Wait()

  t1 := time.Now()

 fmt.Printf("t6c:  %v\n",
    t1.Sub(t0));

}

func f6d_2(counter *hits, wg *sync.WaitGroup) {

  for j:=0;j< 1000000; j++ {

    //counter.RLock()
    counter.n++
    //counter.RUnlock()

    y := 0
    for i:=0;i<100;i++ {
      y += (i * 2) + i
    }
  }
  wg.Done()
}

func f6d() {

  var h hits
  var wg sync.WaitGroup

  wg.Add(4)

  t0 := time.Now()

  for i := 0;i < 4; i++ {
    go f6d_2(&h, &wg)
  }

  wg.Wait()

  t1 := time.Now()

 fmt.Printf("t6d:  %v\n",
    t1.Sub(t0));

}

func main() {
  f6()
  f6a()
  f6b()
  f6c()
  f6d()


  f1()
	f5()
  f5a()
  f5b()
  f5c()
}
