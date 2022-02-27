set -e
[ ! -d "bin" ] && mkdir bin

FLAGS="-Wall -Werror -std=c99"
FILES="../main.c ../draw/*.c"

pushd bin
gcc -c $FILES $FLAGS -I ../include -I ~/Coding/C/SDL2/include
gcc *.o -o out.exe -L ~/Coding/C/SDL2/lib -lmingw32 -lSDL2main -lSDL2
popd

# rm bin/*.o