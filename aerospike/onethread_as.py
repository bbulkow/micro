#!/usr/bin/env python

# import the module
import aerospike
import random
import time
import sys

# Configure the client
config = {
  'hosts': [ ('172.16.109.128', 3000) ]
}

# Create a client and connect it to the cluster
try:
  client = aerospike.client(config).connect()
except:
  import sys
  print("failed to connect to the cluster with", config['hosts'])
  sys.exit(1)

# Records are addressable via a tuple of (namespace, set, key)
ns = 'test'
set = 'test'

nkeys = 100000
nreads = 10000000
firstNames = ('John', 'Barry', 'Harry', 'Sally', 'Frank', 'Joseph', 'Ronen', 'Andy', 'Sammie', 'Jane', 'Zed')
lastNames = ('Chu', 'Srinivasan', 'Mankoski', 'Botzer', 'Dillon', 'Boone', 'Stivers', 'Zombie' )

key = ('test', 'demo', 'foo')

# write some data ( nkeys )
t0 = float(time.clock())

for x in xrange(0, nkeys):
	kstr = 'k' + str(x)
	key = (ns, set, kstr)

	try:
	  # Write a record
	  client.put(key, {
		'name': random.choice(firstNames) + ' ' + random.choice(lastNames) ,
		'age': random.randint(10,100) ,
		'value' : x
	  })
	except Exception as e:
	  print('write error {0}'.format(e))
	if x % 10000 == 0 :
		#print( 'time: {0} records in {1} sec'.format(x, float(time.clock()) - t0) )
		print( 'time: {0} records in {1} sec'.format(x, time.time() ) )


# Read records
t0 = float(time.clock())

for x in xrange(0, nreads):
	kstr = 'k' + str(random.randint(0,nkeys))
	key = (ns, set, kstr )
	(key, metadata, record) = client.get(key)
	
	if x % 10000 == 0 :
		print( 'record is : {0}'.format(repr(record)) )
		#print( 'time: {0} records in {1} sec'.format(x, float(time.clock()) - t0) )
		print( 'time: {0} records in {1} sec'.format(x, time.time() ) )


# Close the connection to the Aerospike cluster
client.close()
