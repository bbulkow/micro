import time;

def f1():
	start = float(time.clock())
	x = 10
	for i in range(100000):
		x = ( 2 * x ) + x + 1;
#	print "t1 answer %d time %f" % (x, float(time.clock()) - start) 
	print("f1 time %f seconds" % ( float(time.clock()) - start)) 

def f2():

  t0 = float(time.clock())

  nStrings = 1000
  nCats = 100000

  a1 = []
  c = ord('a')
  a1.append( str(c) )

  for i in range(1,nStrings):
    c += 1
    a1.append ( a1[i-1] + str(c) )

  t1 = float(time.clock())

  a2 = []
  for i in range(0,nCats):
    a2.append(  a1[i % len(a1)] + a1[(i+7)%len(a1)] + a1[(i+17)%len(a1)] + a1[(i+27)%len(a1)] + a1[(i+37)%len(a1)] + a1[(i+47)%len(a1)] + a1[(i+57)%len(a1)] )

  t2 = float(time.clock())

  a3 = []
  for i in range(0,nCats):
    a7 = []
    a7.append( a1[i%len(a1)] )
    a7.append( a1[(i+7)%len(a1)] )
    a7.append( a1[(i+17)%len(a1)] )
    a7.append( a1[(i+27)%len(a1)] )
    a7.append( a1[(i+37)%len(a1)] )
    a7.append( a1[(i+47)%len(a1)] )
    a7.append( a1[(i+57)%len(a1)] )

    a3.append ( "".join( a7 ) )

  t3 = float(time.clock())

  print("f2 createstr %f sec , plus cat %f sec, join %f sec" % ( t1 - t0, t2 - t1, t3 - t2)) 


def f5():
  start = float(time.clock())
  for x in range(1000000):
     a = {}
     for a1 in range(50):
        a[a1] = str(a1)
  print("f5 %f seconds" % (time.clock() - start)) 

print("quick performance test")
f1()
f2()
f5()
print("end quick performance test")