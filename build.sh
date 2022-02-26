set -e
[ ! -d "./bin" ] && mkdir bin

FLAGS="-Wall -Werror -Wextra -O2 -std=c99"
INCLUDES="main.c emulator/*.c"
gcc $FLAGS -o bin/out.exe $INCLUDES
