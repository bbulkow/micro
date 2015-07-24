import java.util.Date;
import java.util.HashMap;
import java.math.*;


// for futures, compare to Go
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.Callable;

public class micro {

	public static void t1() {

		long t0 = new Date().getTime();

		long x = 10;

		// odd, increasing the loop size an order of magnitude doesn't increase
		// the runtime
		for (int i=0; i < 1000000; i++) {
			x = ( 2 * x ) + x + 1 ;
		}

		long t1 = new Date().getTime();

		BigInteger x_b = new BigInteger("10");

		// odd, increasing the loop size an order of magnitude doesn't increase
		// the runtime
		BigInteger two = new BigInteger("2");
		for (int i=0; i < 100000; i++) {
			BigInteger x2_b = x_b.add( BigInteger.ONE );
			BigInteger x3_b = x_b.multiply(two);
			x_b = x2_b.add(x3_b);
		}

		long t2 = new Date().getTime();

		System.out.printf("f1: time1 %.3f time2 %.3f \n", 
			(float) (t1-t0) / 1000.0, (float) (t2 - t1) / 1000);

	}


	public static void t5() {

		long t0 = new Date().getTime();

		for (int x=0; x < 1000000; x++) {
			HashMap<Integer, String> a = new HashMap<Integer, String>();
			for (int a1=0; a1 < 50; a1++) {
				a.put(a1, Integer.toString(a1) );
			}
		}

		long t1 = new Date().getTime();

		System.out.printf("f5: %.3f \n", (float) (t1-t0) / 1000.0);

	}

    public static void main(String[] args) {
        System.out.println("java microbenchmark");
        t1();
        t5();
    }

}