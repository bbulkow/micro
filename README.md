# Microbenchmarks

## Purpose

Although "microbenchmarks are evil", there's a sense in which they are not.

Specifically, if I'm writing code in a language, I have to know the relative benefits and weaknesses of different structures in a language. If small maps are fast and large maps are slow, I might need to make use of that.

There's a theory of coding that one should never do that. One should code to some kind of abstract truth, and complain if the language doesn't do that well.

## Tests

Right now the tests are minimal. I did code about 10 instructive benchmarks
in different languages .... then I lost it all, because I didn't github it.

t1 is a basic loop and math test. It should be fast, but... how fast? And what
kind of integers? t1 should cover both 'native ints' and bigints. Some languages, like python, only supply bigints, and some like Java support both (but bigints are annoying to use.

t5 is a basic test to create maps and insert data. Does not stress retrieving.

# notes about C and C++

In the C++ test, we see that the -O3 flag is critical. Without -O3, C++ is so much slower than python
that we might say C is bringing a stone axe to a gunflight. C++ certainly doesn't get up to the speed
of the fast languages, like Java, PHP7, and node/js. With C++, we see that at least C++ is getting up
to the speed of python.

In C++'s defense, I might say "it's easy to write slow code in any language", but I might also say 
that if idomatic code is slow, the language is slow. The goal of this tool is to test IDOMATIC code.

One problem with C++ is that you're relying on the underlying, thread safe, allocator that the system provides.
Some of the tests stress the memory allocation system, which is of unknown quality. At least, then,
let's test with something more stable and known to be fast. Thus, the inclusion of testing using the JEMalloc
allocator, which can be dropped into a directory. The current "run" script works against OSX, which has
unusual linkage needs.

We still see idiomatic C++ running about 8x slower than Java, PHP7, and Node.