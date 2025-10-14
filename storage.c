/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/9/2025
* Lab 6: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

#include <stdio.h>
#include <string.h>
#include "VectorArray.h"
#include "storage.h"


#define MAX_VECTORS 10
static Vector memory[MAX_VECTORS];  //max memory for vectors 

int addVector(Vector v){        //vector is being added to the array
    //first name check, and replace 
    for(int i = 0; i < MAX_VECTORS; i++){
        if(memory[i].used && strcmp(memory[i].name, v.name) == 0){ //check flag and name
            memory[i] = v; //set empty slot to v
            return 1;
        }
    }
    //if not the case, just search for an empty slot
    for(int i = 0; i < MAX_VECTORS; i++){ 
        if(memory[i].used != 1){ //find empty slot, first iteration of unsused
            memory[i] = v; //set empty slot to v
            memory[i].used = 1; //mark as used
            return 1; 
        }
    }
    printf("ERROR! This vector cannot be added to the array.\n");
    return 0; 
}

void clearVectors(){
    for(int i = 0; i < MAX_VECTORS; i++){
        memory[i].used = 0;    //mark all as unused
    }
    printf("Memory cleared.\n");
}

void listVectors(){
    printf("Stored Vectors: \n");
    for(int i = 0; i < MAX_VECTORS; i++){
        if(memory[i].used){
            printf("%s = %.2f %.2f %.2f \n",
            memory[i].name,
            memory[i].x,
            memory[i].y,
            memory[i].z);
        }
    }
}

Vector* findVector(char* name){ 
    for(int i = 0; i < MAX_VECTORS; i++){
        if(memory[i].used == 1 && strcmp(memory[i].name, name) == 0){
            return &memory[i];  //pointer to vector
        } 
    }
    return NULL; //not found otherwise
}