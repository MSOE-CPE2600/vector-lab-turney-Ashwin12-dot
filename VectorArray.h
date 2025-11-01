/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/
#ifndef VECTORARRAY_H
#define VECTORARRAY_H

#include <stdio.h>

//struct to represent a 3D vector
typedef struct{
    char name[10];   //name of the vector (like a, b, c)
    double x, y, z;  //components of the vector
    int used;        //flag to mark if the vector slot is used
} Vector; 

//core vector operations
Vector add(Vector a, Vector b);
Vector subtract(Vector a, Vector b);
Vector scalarMultiply(Vector a, double s);

//extra credit - dot and cross products 
double dotProduct(Vector a, Vector b);
Vector crossProduct(Vector a, Vector b);

#endif
