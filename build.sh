mkdir -p build
cd build || exit
cmake ../
make -j 8
mv jvc ../
cd ..