# so slow we comment it out
#echo "Compile C++ with no flags"
#rm micro
#g++ micro.cpp -o micro
#./micro

echo "Compile C++ with much better flags"
rm micro
g++ -O3 -march=native micro.cpp -o micro
./micro

JEMALLOC=~/dev/jemalloc/jemalloc-4.0.4
echo "Running JEMALLOC. This needs SUDo because it overrides files in /usr/local/lib. BEWARE."
rm micro
sudo cp $JEMALLOC/lib/* /usr/local/lib
g++ -O3  -L$JEMALLOC/lib micro.cpp -o micro -ljemalloc 
#g++ -I$JEMALLOC/include -L$JEMALLOC/lib $JEMALLOC  micro.cpp -o micro -ljemalloc
./micro