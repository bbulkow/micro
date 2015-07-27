<?hh // strict


function f1() {
	float $t0 = microtime(true);
	int $x = 10;
	for (int $i = 0; $i < 100000; ++$i) {
		$x = ( 2 * $x ) + $x + 1;
	}
	float $t1 = microtime(true);
	
	printf( "t1 result %d time %f seconds no t2 bigSecs\n" , $x, $t1 - $t0 );
}

function f1a() {
	float $t0 = microtime(true);
	int $x = 10;
	int $i = 0;
	do {
		$x = ( 2 * $x ) + $x + 1;
		++$i;
	} while ($i < 100000);
	float $t1 = microtime(true);

	printf( "t1a result %d time %f sec no t2\n" , $x, $t1 - $t0 );
}


function f2() {
	float $t0 = microtime(true);

	int $nStrings = 1000;
	int $nCats = 100000;

	Vector<string> $a1 = Vector{};
	int $c = ord( "a" );
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
f5();
print "end quick performance test\n";
