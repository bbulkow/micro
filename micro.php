<?php


function t1() {
	$start = microtime(true);
	$x = 10;
	for ($i = 0; $i < 100000; ++$i) {
		$x = ( 2 * $x ) + $x + 1;
	}
#	print "t1 answer %d time %f" % (x, float(time.clock()) - start) 
	printf( "t1 result %d time %f seconds\n" , $x, microtime(true) - $start );
}

function t1a() {
	$start = microtime(true);
	$x = 10;
	$i = 0;
	do {
		$x = ( 2 * $x ) + $x + 1;
		++$i;
	} while ($i < 100000);
#	print "t1 answer %d time %f" % (x, float(time.clock()) - start) 
	printf( "t1a result %d time %f seconds\n" , $x, microtime(true) - $start );
}


function t5() {
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
t1();
t1a();
t5();
print "end quick performance test\n";
?>