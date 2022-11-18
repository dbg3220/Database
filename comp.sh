#!/bin/bash

## Modify this compilation file whenever a new C source file is added

CFLAGS="-std=c99 -ggdb -Wall -Wextra -I dep/"
C_FILES="main.c database.c student.c"
OBJ_FILES="database.o student.o dep/ListADT.o"
TARGETS=("main")

gcc $CFLAGS -c $C_FILES
echo "Compiled $C_FILES into object files"

for target in ${TARGETS[@]}; do
	gcc $CFLAGS -o $target "${target}.o" $OBJ_FILES
	echo "Linked ${target}.o $OBJ_FILES to create executable '$target'"
done

rm *.o
echo "Removed object files to clean directory"

