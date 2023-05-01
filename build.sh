mkdir -p build
cd build || exit
#cmake -DCMAKE_CXX_COMPILER=clang++ ../
cmake ../
make -j 8
mv jvc ../
cd ..

mkdir -p lib
mv build/third_party/bdwgc/libgc.so lib/