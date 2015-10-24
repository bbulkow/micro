echo "Compile C++ the normal way"
g++ micro.cpp -o micro
./micro
echo "Compile C++ with much better flags"
g++ -O3 -march=native micro.cpp -o micro
./micro


