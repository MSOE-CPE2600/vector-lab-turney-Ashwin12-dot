/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/9/2025
* Lab 6: Vector calculator
* 
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

#include "VectorArray.h"
#include "storage.h"
#include "userinterface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void showHelp(){
    printf("\nMiniMat Vector Calculator Help:\n");
    printf("Commands:\n");
    printf("var = x y z : Defines a vector named 'var' with components x, y, z\n");
    printf("var = x + y : Adds vec1 and vec2, stores in result_vec\n");
    printf("var = y - x : Subtracts vec2 from vec1, stores in result_vec\n");
    printf("var = x * scalar(1,2,3 etc) : Multiplies vec by scalar, stores in result_vec\n");
    printf("A . B : Computes dot product of vec1 and vec2\n");
    printf("A X B : Computes cross product of vec1 and vec2, stores in result_vec\n");
    printf("list : Lists all stored vectors\n");
    printf("clear : Clears all stored vectors\n");
    printf("-h : Displays this help message\n");
    printf("quit : Exits the program\n");
}

void runInterface(int argc, char* argv[]){
    char input[100]; //buffer for input, character array - string 
    char left[10], right[10], resultname[10], name[10], op; 
    double x = 0, y = 0, z = 0, scalar = 0; // debugging 

    //check if they did -h right away
    if(argc > 1 && (strcmp(argv[1], "-h") == 0)){
        showHelp();
        return;
    }

    printf("MiniMat Vector Calculator. Type -h for help.\n");
    while(1) {
        fgets(input, sizeof(input), stdin); //get user input

        //remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // printf("%s", input); //echo input for debugging

        //check for quit command
        if(strcmp(input, "quit") == 0){
            printf("\nExiting MiniMat. Goodbye!\n");
            break;
        }

        //check for help command
        else if(argc > 1 && strcmp(input, "-h") == 0 || strcmp(input, "-h") == 0){
            showHelp();
            continue;
        }

        //check for list command
        else if(strcmp(input, "list") == 0){
            listVectors();
            continue;
        }

        //check for clear command
        else if(strcmp(input, "clear") == 0){
            clearVectors();
            continue;
        } 

        else if(strcmp(input, "") == 0){
            continue; //ignore empty input
        }

        //ARITHMETIC TIME!!!!
        if(strstr(input, "=") != NULL){ //if input contains =
            //modify input, split out the = sign so we can parse it
            char temp[100];
            strcpy(temp, input);

            //edge case -> commas!
            for(int i = 0; i < strlen(temp); i++){
                if(temp[i] == ','){
                    temp[i] = ' ';
                }
            }

            //parse it
            if(sscanf(temp, "%s = %lf %lf %lf", name, &x, &y, &z) == 4){
                Vector v = {"", x, y, z, 1}; //create vector
                strcpy(v.name, name); //set name

                if(addVector(v)){
                    printf("Vector %s added: %.2f %.2f %.2f\n", v.name, v.x, v.y, v.z);
                } else {
                    printf("Failed to add vector %s.\n", v.name);
                }
                continue;
            }

            //check for addition or subtraction or scalar multiply
            if(sscanf(input, "%s = %s %c %s", resultname, left, &op, right) == 4){
                Vector *v1 = findVector(left);
                Vector *v2 = findVector(right);

                if(v1 == NULL && op != '*'){
                    printf("One or both vectors not found.\n");
                    continue;
                }

                if(op == '+'){
                    if(v1 != NULL && v2 != NULL){       //check if vectors are found
                        Vector result = add(*v1, *v2);      //add them
                        strcpy(result.name, resultname);    //set result name
                        if(addVector(result)){ //store result into list
                            printf("Result %s = %.2f %.2f %.2f\n", 
                                   result.name, result.x, result.y, result.z);//print result
                        } else {
                            printf("Failed to store result vector %s.\n", result.name);//error handling
                        }
                    }
                } 
                else if (op == '-'){
                    if(v1 != NULL && v2 != NULL){
                        Vector result = subtract(*v1, *v2);
                        strcpy(result.name, resultname);
                        if(addVector(result)){
                            printf("Result %s = %.2f %.2f %.2f\n", 
                                   result.name, result.x, result.y, result.z);
                        } else {
                            printf("Failed to store result vector %s.\n", result.name);
                        }
                    }
                } 
                else if (op == '*'){ //Vector * scalar
                    if (v1 && sscanf(right, "%lf", &scalar) == 1){
                        Vector result = scalarMultiply(*v1, scalar);
                        strcpy(result.name, resultname);
                        if(addVector(result)){
                            printf("Result %s = %.2f %.2f %.2f\n", 
                                   result.name, result.x, result.y, result.z);
                        } else {
                            printf("Failed to store result vector %s.\n", result.name);
                        }
                    } else {
                        printf("Invalid scalar multiplication command.\n");
                    }
                }
                continue;
            } 
            else {
                printf("Unrecognized command. Type -h for help.\n");
                continue;
            }
        } 
        else if (sscanf(input, "%s . %s", left, right) == 2){ //dot product
            Vector *v1 = findVector(left);
            Vector *v2 = findVector(right); 
            if(v1 == NULL || v2 == NULL){
                printf("\nOne or both vectors not found.\n");
                continue;
            }
            double result = dotProduct(*v1, *v2);
            printf("\nDot product of %s and %s = %.2f\n", v1->name, v2->name, result);
        } 
        else if (sscanf(input, "%s X %s", left, right) == 2){ //cross product
            Vector *v1 = findVector(left);
            Vector *v2 = findVector(right);
            if(v1 == NULL || v2 == NULL){
                printf("\nOne or both vectors not found.\n");
                continue;
            }
            Vector result = crossProduct(*v1, *v2);
            strcpy(result.name, "temp");
            if(addVector(result)){
                printf("Cross product of %s and %s = %.2f %.2f %.2f\n", 
                       v1->name, v2->name, result.x, result.y, result.z);
            } else {
                printf("Failed to store result vector.\n");
            }
        }  
        else if (sscanf(input, "%s %c %s", left, &op, right) == 3){  //operations without equals
            Vector *v1 = findVector(left);
            Vector *v2 = findVector(right);
            Vector result;

          

            if (op == '+'){
                
            if(v1 == NULL || v2 == NULL){
                printf("One or both vectors not found.\n");
                continue;
            }
                result = add(*v1, *v2);
            } else if (op == '-'){
                
            if(v1 == NULL || v2 == NULL){
                printf("One or both vectors not found.\n");
                continue;
            }
                result = subtract(*v1, *v2);
            } else if (op == '*'){ //Vector * scalar
                result = scalarMultiply(*v1, atof(right));    //convert string to double
            } //do scalar * vector eventually 
            else {
                printf("Unrecognized operation '%c'. Type -h for help.\n", op);
                continue;
            }

            printf("\nResult %.2f %.2f %.2f\n", 
                result.x, result.y, result.z);
        } else {
            printf("Unrecognized command. Type -h for help.\n");
            continue;      
        }
    }

}

