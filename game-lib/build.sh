rm -rf build
mkdir build
echo "Recreated build directory"

cd build
cmake ../ && cmake --build .

cd ..
rm -rf dist
mkdir dist
cp ./build/GameOfLife ./dist/GameOfLife
cp ./build/libgameoflife.a ./dist/gameoflife.a
cp ./src/game_of_life.h ./dist/game_of_life.h

echo "Build successful!"
