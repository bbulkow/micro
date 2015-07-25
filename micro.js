
function t1() {
	start = process.hrtime();
	x = 10;
	for (var i = 0; i < 100000; i++) {
		x = ( 2 * x ) + x + 1;
	}
	end = process.hrtime(start);
	console.log( "t1 result %d: time %d s %d ms" , x, end[0], end[1]/1000000 );
}

function t1a() {
	start = process.hrtime();

	x = 10;
	i = 0;
	do {
		x = ( 2 * x ) + x + 1;
		i++;
	} while (i < 100000);
	end = process.hrtime(start);
	console.log( "t1a result %d: %d s %d ms" , x, end[0], end[1]/1000000 );
}


function t5() {
  start = process.hrtime();

  for ( var i = 0; i < 1000000; i++) {
     a = {};
     for (var a1 = 0; a1 < 50; a1++ ) {
        a[a1] = a1.toString();
     }
  }
  end = process.hrtime(start);
  console.log( "t5 %d s %d ms" , end[0], end[1]/1000000 );
}

console.log("quick performance test");
t1();
t1a();
t5();
console.log( "end quick performance test");

