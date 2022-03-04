set -e
[ ! -d "bin" ] && mkdir bin

FLAGS="-Wall -Werror -Wformat-truncation -Wformat-overflow -Wextra -std=c99"
FILES="../*/*.c ../*.c"

pushd bin
gcc -c $FILES $FLAGS -I ../include -I ~/Coding/C/SDL2/include
gcc *.o -o out.exe -L ~/Coding/C/SDL2/lib -lmingw32 -lSDL2main -lSDL2
popd

# rm bin/*.o