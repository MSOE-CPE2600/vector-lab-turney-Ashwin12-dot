# Vector Calculator 8


## Overview
This is a program which is a basic vector calculator, it also features dynamic memory allocation, meaning unlimited amount of vectors if the input is correct. It achieves this by using the malloc command and properly utilizes valgrind to ensure there are no memory leaks in the code - implemented by a free function, this function is viewable in the storage.c file where most of the magic happens.

## Available Commands

### Program commands
- list (lists the vectors you currently have in memory)
- clear (clears vectors in memory)
- save (.csv filename)
- load (.csv filename)
- quit (exits the program!)
## Vector operations
operations: 
- "x + y" 
- "b - y"
- "c X y" 
- "b . a" 


### Build Instructions
Compile the program using "gcc" or a Makefile if made

Compile: 

gcc -o vector_calc userinterface.c storage.c VectorArray.c main_lab5.c -lm

#### Run Instructions
./run_lab5
