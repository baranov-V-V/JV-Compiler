sudo mkdir -p build
cd build || exit
#cmake -DCMAKE_CXX_COMPILER=clang++ ../
cmake ../
make -j 8
mv jvc ../
cd ..

if [ ! -f /usr/lib/jvc/gc/libgc.so ]
then
  echo "File does not exist"
  sudo mkdir -p /usr/lib/jvc/gc
  cp build/third_party/bdwgc/libgc.so /usr/lib/jvc/gc/
fi