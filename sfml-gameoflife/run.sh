cp ../game-lib/dist/game_of_life.h ./includes/game_of_life.h
cp ../game-lib/dist/game_of_life.a ./libs/game_of_life.a

rm -rf build
mkdir build
echo "Recreated build directory"

cd build
cmake ../ && cmake --build .

echo "Build successful!"

cd ..
rm -rf dist
mkdir dist
cp ./build/SFMLGameOfLife ./dist/GameOfLife
./dist/GameOfLife