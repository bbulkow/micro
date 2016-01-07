#!/usr/bin/env python

# import the module
import aerospike
import random
import time
import sys
import threading

# Configure the client
config = {
  'hosts': [ ('172.16.109.128', 3000) ]
}

# Create a client and connect it to the cluster
try:
  client = aerospike.client(config).connect()
except:
  print("failed to connect to the cluster with", config['hosts'])
  sys.exit(1)

# Records are addressable via a tuple of (namespace, set, key)
ns = 'test'
set = 'test'

g_nkeys = 10000
g_nreads = 10000000
firstNames = ('John', 'Barry', 'Harry', 'Sally', 'Frank', 'Joseph', 'Ronen', 'Andy', 'Sammie', 'Jane', 'Zed')
lastNames = ('Chu', 'Srinivasan', 'Mankoski', 'Botzer', 'Dillon', 'Boone', 'Stivers', 'Zombie' )

nthreads = 4

def writeWork(nKeys, thrName):

	# write some data ( nkeys )
	t0 = float(time.time())

	for x in xrange(0, nKeys):
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
			print( 'thr {0} time: {1} records in {2} sec'.format(thrName, x, float(time.time()) - t0) )

def readWork(nReads, thrName):
	global g_nkeys
	global client

	print(' thr {0} is starting with nreads {1}'.format(thrName,nReads))

	# Read records
	t0 = float(time.time())

	for x in xrange(0, nReads):
		kstr = 'k' + str(random.randint(0,g_nkeys))
		key = (ns, set, kstr )
		try:
			(key, metadata, record) = client.get(key)
		except aerospike.exception.ClientError as e:
			print('Aerospike Error: {0} [{1}]'.format(e.msg, e.code))
			return None
		
		print( 'record is : {0}'.format(repr(record)) )
		print( 'thr {0} time: {1} records in {2} sec'.format(thrName, x, float(time.time()) - t0) )

# write your data
writeWork(g_nkeys, "def")

# for nthreads, read
for i in range(nthreads):
	t = threading.Thread(target=readWork, args=(g_nreads / nthreads, str(i)))
	t.start()


# Close the connection to the Aerospike cluster
client.close()
