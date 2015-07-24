import time;

def t1():
	start = float(time.clock())
	x = 10
	for i in xrange(100000):
		x = ( 2 * x ) + x + 1;
#	print "t1 answer %d time %f" % (x, float(time.clock()) - start) 
	print "t1 time %f seconds" % ( float(time.clock()) - start) 


def t5():
  start = float(time.clock())
  for x in xrange(1000000):
     a = {}
     for a1 in xrange(50):
        a[a1] = str(a1)
  print "t5 %f seconds" % (time.clock() - start) 

print "quick performance test"
t1()
t5()
print "end quick performance test"