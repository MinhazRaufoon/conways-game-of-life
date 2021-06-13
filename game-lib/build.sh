rm -rf build
mkdir build
echo "Recreated build directory"

cd build
cmake ../ && cmake --build .

cd ..
rm -rf dist
mkdir dist
cp ./build/GameOfLife ./dist/GameOfLife

echo "Build successful!"
