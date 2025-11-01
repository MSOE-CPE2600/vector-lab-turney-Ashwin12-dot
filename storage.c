/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "VectorArray.h"
#include "storage.h"

static Vector *memory = NULL;  // pointer to dynamically allocated array of vectors
int count = 0;                 // how many vectors currently stored
int capacity = 0;              // current size of allocated array

// load
void loadVectors(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s for reading. File may be missing.\n", filename);
        return;
    }

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        char name[10];
        double x, y, z;

        int read_in = sscanf(line, "%[^,],%lf,%lf,%lf", name, &x, &y, &z); //regex style reading

        if (read_in == 4) {
            Vector v;
            strcpy(v.name, name);
            v.x = x;
            v.y = y;
            v.z = z;
            v.used = 1;
            addVector(v);
        } else {
            printf("File isn't in a correct format for csv.\n"); //error handling
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Vectors loaded from %s\n", filename);
}

// save
void saveVectors(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        if (memory[i].used) {
            fprintf(file, "%s,%lf,%lf,%lf\n",   //no need for regex here, just write to file
                memory[i].name,
                memory[i].x,
                memory[i].y,
                memory[i].z);
        }
    }

    fclose(file);
    printf("Vectors saved to %s\n", filename);
}

// helper method i decided to make
Vector *reallocVectors(Vector *oldMemory, int oldSize, int newSize) {
    Vector *newMemory = (Vector *)malloc(newSize * sizeof(Vector));
    if (newMemory == NULL) {
        printf("Memory allocation failed while resizing.\n"); //STILL FAILED VALGRIND!!!!
        return oldMemory;
    }

    memcpy(newMemory, oldMemory, oldSize * sizeof(Vector));
    free(oldMemory);
    return newMemory;
}

// add
int addVector(Vector v) {
    if (count == capacity) {
        memory = reallocVectors(memory, capacity, capacity + 10);
        if (memory == NULL) {
            return 0;
        } else {
            capacity += 10;
        }
    }

    for (int i = 0; i < count; i++) {
        if (memory[i].used && strcmp(memory[i].name, v.name) == 0) {
            memory[i] = v;
            return 1;
        }
    }

    memory[count] = v;
    memory[count].used = 1;
    count++;
    return 1;
}


// clear
void clearVectors() { //deallocate memory for vectors in the program but don't touch the files they are saved too
    free(memory);
    memory = NULL;
    count = 0;
    capacity = 0;
    printf("Memory cleared.\n");
}

// list vectors
void listVectors() {
    if (count == 0) {
        printf("No vectors stored.\n");
        return;
    }

    printf("Stored Vectors:\n");
    for (int i = 0; i < count; i++) {
        if (memory[i].used) {
            printf("%s = %.2f %.2f %.2f\n",
                memory[i].name,
                memory[i].x,
                memory[i].y,
                memory[i].z);
        }
    }
}

// find - just a for loop!
Vector *findVector(char *name) {
    for (int i = 0; i < count; i++) {
        if (memory[i].used == 1 && strcmp(memory[i].name, name) == 0) {
            return &memory[i];
        }
    }
    return NULL;
}

//need to pass valgrind, added this method, called it in userinterface for the quit function
void freeAllVectors(){
    if(memory != NULL){
        free(memory); //free memory
        memory = NULL; //null check
    }
    count = 0; //reset everything
    capacity = 0; 
}
