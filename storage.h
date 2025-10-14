/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/9/2025
* Lab 6: Vector Calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/



#include "VectorArray.h"

//core storage operations
int addVector(Vector v);          //take in a vector to add
Vector* findVector(char* name);   //use a pointer, to find the address in memory
void clearVectors();              //clears all stored vectors
void listVectors();               //lists all vectors in memory
