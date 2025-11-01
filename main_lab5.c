/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

#include "userinterface.h"
#include "VectorArray.h"
#include "storage.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    runInterface(argc, argv); //pass command line args to interface
    return 0; 
}