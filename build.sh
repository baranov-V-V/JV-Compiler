mkdir -p build
cd build || exit
#cmake -DCMAKE_CXX_COMPILER=clang++ ../
cmake ../
make
mv jvc ../
cd ..