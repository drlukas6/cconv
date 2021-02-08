mkdir build
cd build
cmake ..
make
cp cconv /usr/local/bin
cd ..
rm -r build
