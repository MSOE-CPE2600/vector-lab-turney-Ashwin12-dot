/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

//adding guards because my program wasnt compiling without them 
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <stdio.h>
#include "VectorArray.h"
#include "storage.h"

void runInterface(int argc, char* argv[]); //argc and argv for command line args
void showHelp(); //function to show help message
#endif          //USERINTERFACE_H  
