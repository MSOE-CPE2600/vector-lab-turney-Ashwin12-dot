/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/



#ifndef STORAGE_H
#define STORAGE_H

#include "VectorArray.h"

// Global variables
extern int count;
extern int capacity;

// Function declarations - modified for lab 7 from lab 5
int addVector(Vector v);
void clearVectors();
void listVectors();
Vector* findVector(char* name);

//lab 7 functions 
void loadVectors(char* filename);
void saveVectors(char* filename);

//valgrind pass
void freeAllVectors();

#endif

