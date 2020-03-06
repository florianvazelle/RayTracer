rm -r build/
mkdir build
cd build/
cmake ..
make -j 4
cd ..
./build/RayTracer
feh rendu.tga
