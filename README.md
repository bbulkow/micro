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

