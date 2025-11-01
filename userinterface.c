/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

#include "VectorArray.h"
#include "storage.h"
#include "userinterface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void showHelp() {
    printf("\nMiniMat Vector Calculator Help:\n");
    printf("Commands:\n");
    printf("var = x y z : Defines a vector named 'var' with components x, y, z\n");
    printf("var = x + y : Adds vec1 and vec2, stores in result_vec\n");
    printf("var = y - x : Subtracts vec2 from vec1, stores in result_vec\n");
    printf("var = x * scalar : Multiplies vec by scalar, stores in result_vec\n");
    printf("A . B : Computes dot product of vec1 and vec2\n");
    printf("A X B : Computes cross product of vec1 and vec2, stores in result_vec\n");
    printf("list : Lists all stored vectors\n");
    printf("clear : Clears all stored vectors\n");
    printf("-h : Displays this help message\n");
    printf("load filename : Loads vectors from a file\n");
    printf("save filename : Saves vectors to a file\n");
    printf("quit : Exits the program\n");
}

void runInterface(int argc, char* argv[]) {
    char input[100];
    char left[10], right[10], resultname[10], name[10], op;
    double x = 0, y = 0, z = 0, scalar = 0;

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        showHelp();
        return;
    }

    printf("MiniMat Vector Calculator. Type -h for help.\n");
    printf("Begin typing on the next free, empty line. \n"); //added prompt from demo

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // remove newline

        if (strcmp(input, "quit") == 0) {
            printf("\nExiting MiniMat. Goodbye!\n");
            freeAllVectors();
            break;
        } else if (strcmp(input, "-h") == 0) {
            showHelp();
            continue;
        } else if (strcmp(input, "list") == 0) {
            listVectors();
            continue;
        } else if (strcmp(input, "clear") == 0) {
            clearVectors();
            continue;
        } else if (strcmp(input, "") == 0) {
            continue;
        }


        //only 2 things i added for lab7, implement load and save
        else if (strncmp(input, "load ", 5) == 0) {
            char filename[50];
            if (sscanf(input + 5, "%s", filename) != 1) { //sscanf to read from input after "load "
                printf("Invalid load command. Usage: load filename\n");
                continue;
            }
            loadVectors(filename);
            continue;
        }

        else if (strncmp(input, "save ", 5) == 0) { //similar to load
            char filename[50];
            if (sscanf(input + 5, "%s", filename) != 1) { //sscanf to read from input after "save "
                printf("Invalid save command. Usage: save filename\n");
                continue;
            }
            saveVectors(filename);
            continue;
        }

        else if (strstr(input, "=") != NULL) {
            char temp[100];
            strcpy(temp, input);

            for (int i = 0; i < strlen(temp); i++) {
                if (temp[i] == ',') temp[i] = ' ';
            }

            if (sscanf(temp, "%s = %lf %lf %lf", name, &x, &y, &z) == 4) {
                Vector v = {"", x, y, z, 1};
                strcpy(v.name, name);
                if (addVector(v)) {
                    printf("Vector %s added: %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
                } else {
                    printf("Failed to add vector %s.\n", v.name);
                }
                continue;
            }

            if (sscanf(input, "%s = %s %c %s", resultname, left, &op, right) == 4) {
                Vector *v1 = findVector(left);
                Vector *v2 = findVector(right);

                if (v1 == NULL && op != '*') {
                    printf("One or both vectors not found.\n");
                    continue;
                }

                if (op == '+') {
                    Vector result = add(*v1, *v2);
                    strcpy(result.name, resultname);
                    addVector(result);
                    printf("Result %s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                } else if (op == '-') {
                    Vector result = subtract(*v1, *v2);
                    strcpy(result.name, resultname);
                    addVector(result);
                    printf("Result %s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                } else if (op == '*') {
                    if (v1 && sscanf(right, "%lf", &scalar) == 1) {
                        Vector result = scalarMultiply(*v1, scalar);
                        strcpy(result.name, resultname);
                        addVector(result);
                        printf("Result %s = %.2f %.2f %.2f\n", result.name, result.x, result.y, result.z);
                    } else {
                        printf("Invalid scalar multiplication command.\n");
                    }
                }
                continue;
            } else {
                printf("Unrecognized command. Type -h for help.\n");
                continue;
            }
        }

        // ----- DOT PRODUCT -----
        else if (sscanf(input, "%s . %s", left, right) == 2) {
            Vector *v1 = findVector(left);
            Vector *v2 = findVector(right);
            if (v1 == NULL || v2 == NULL) {
                printf("\nOne or both vectors not found.\n");
                continue;
            }
            double result = dotProduct(*v1, *v2);
            printf("\nDot product of %s and %s = %.2f\n", v1->name, v2->name, result);
        }

        // CROSS PRODUCT 
        else if (sscanf(input, "%s X %s", left, right) == 2) {
            Vector *v1 = findVector(left);
            Vector *v2 = findVector(right);
            if (v1 == NULL || v2 == NULL) {
                printf("\nOne or both vectors not found.\n");
                continue;
            }
            Vector result = crossProduct(*v1, *v2);
            strcpy(result.name, "temp");
            addVector(result);
            printf("Cross product of %s and %s = %.2f %.2f %.2f\n",
                   v1->name, v2->name, result.x, result.y, result.z);
        }

        // ARITHMETIC WITHOUT EQUALS 
        else if (sscanf(input, "%s %c %s", left, &op, right) == 3) {
            Vector *v1 = findVector(left);
            Vector *v2 = findVector(right);
            Vector result;

            if (op == '+') result = add(*v1, *v2);
            else if (op == '-') result = subtract(*v1, *v2);
            else if (op == '*') result = scalarMultiply(*v1, atof(right));
            else {
                printf("Unrecognized operation '%c'. Type -h for help.\n", op);
                continue;
            }

            printf("\nResult %.2f %.2f %.2f\n", result.x, result.y, result.z);
        }

        //final block if EVERYTHING fails - had to debug this part a lot - would print a lot of garbage otherwise
        else {
            printf("Unrecognized command. Type -h for help.\n");
            continue;
        }
    }
}
