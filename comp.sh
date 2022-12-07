#!/bin/bash

## Modify this compilation file whenever a new C source file is added

CFLAGS="-std=c99 -ggdb -Wall -Wextra -I dep/"
C_FILES="main.c database.c student.c test.c"
OBJ_FILES="database.o student.o dep/Linked_ListADT.o"
TARGETS=("main" "test")

gcc $CFLAGS -c $C_FILES
echo "gcc $CFLAGS -c $C_FILES"

for target in ${TARGETS[@]}; do
	gcc $CFLAGS -o $target "${target}.o" $OBJ_FILES
	echo "gcc $CFLAGS -o $target ${target}.o $OBJ_FILES"
done

rm *.o
echo "rm *.o"

