<?php

ini_set('memory_limit','1G');

function f1() {
	$start = microtime(true);
	$x = 10;
	for ($i = 0; $i < 100000; ++$i) {
		$x = ( 2 * $x ) + $x + 1;
	}
#	print "t1 answer %d time %f" % (x, float(time.clock()) - start) 
	printf( "f1 result %d time %f seconds\n" , $x, microtime(true) - $start );
}

function f1a() {
	$start = microtime(true);
	$x = 10;
	$i = 0;
	do {
		$x = ( 2 * $x ) + $x + 1;
		++$i;
	} while ($i < 100000);
#	print "t1 answer %d time %f" % (x, float(time.clock()) - start) 
	printf( "f1a (different loop) result %d time %f seconds\n" , $x, microtime(true) - $start );
}

function f2() {
	$t0 = microtime(true);

	$nStrings = 1000;
	$nCats = 100000;

	$a1 = array();
	$c = ord( "a" );
	$a1[0] = (string) chr($c);

	for ($x = 1; $x < $nStrings; $x++) {
		$a1[ $x ] = $a1[ $x - 1] . chr($c);
	}

	$t1 = microtime(true);

	$a2 = array();
	for ($x = 0; $x < $nCats; $x++) {
		$a2[ $x ] = $a1[ $x % count($a1) ] . 
					$a1[ ( $x + 7 ) % count($a1) ] . 
					$a1[ ( $x + 17 ) % count($a1) ] . 
					$a1[ ( $x + 27 ) % count($a1) ] . 
					$a1[ ( $x + 37 ) % count($a1) ] . 
					$a1[ ( $x + 47 ) % count($a1) ] .
					$a1[ ( $x + 57 ) % count($a1) ] ;
	}

	$t2 = microtime(true);

	printf( "f2 string create %f sec cat with dot %f\n" , $t1 - $t0, $t2 - $t1 );

}


function f5() {
  $start = microtime(true);
  for ($i = 0; $i < 1000000; ++$i) {
     $a = array();
     for ($a1 = 0; $a1 < 50; ++$a1 ) {
        $a[$a1] = strval($a1);
     }
  }
  printf( "t5 %f seconds\n",microtime(true) - $start) ;
}

print "quick performance test\n";
f1();
f1a();
f2();
f5();
print "end quick performance test\n";
?>