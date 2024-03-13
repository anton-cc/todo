#!/bin/bash



cd src

gcc -o ../bin/app main.c todolist.c 

cd 

rm src/*.o
rm src/*.out

echo "Build finito"
