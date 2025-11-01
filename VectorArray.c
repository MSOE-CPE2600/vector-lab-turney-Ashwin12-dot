/*
* Name: Ashwin Senthil
* Prof: Dr. Turney
* 10/27/2025
* Lab 7: Vector calculator
*
* compile with: gcc main_lab5.c userinterface.c storage.c VectorArray.c -o minimat -lm OR Makefile
*/

#include "VectorArray.h"
#include <stdio.h>  

//this is basically (a.x + b.x) and so on
Vector add(Vector a, Vector b){
    Vector r = {"", a.x+b.x, a.y+b.y, a.z+b.z, 1}; 
    //so basically we follow struct format, vector array(string), ur double x,y,z
    //then a 1 or 0 at the end just to show if its used or not - a flag

    return r; //we want to return our calculated vec, not 0 like i usually do 
}

//same concept as add, just switch + to -
Vector subtract(Vector a, Vector b){
    Vector r = {"", a.x-b.x, a.y-b.y, a.z-b.z, 1};
    return r; //simple
}

//lab doc says vector * scalar value, so a double maybe?
Vector scalarMultiply(Vector a, double s){
    Vector r = {"", a.x * s, a.y * s, a.z * s, 1}; 
    //its the same vector * s
    return r;
}

//extra credit maybe?

//this is vector multiplication, so scalar, but w 2 vectors
//dotProduct ALWAYS returns a SCALAR value
//so literally j return the multiplied version of a, b
double dotProduct(Vector a, Vector b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//formula: a * b = (aybz - azby, azbx - axbz, axby - aybx)
//confusing but -> returns a vector that is perpendicular
Vector crossProduct(Vector a, Vector b){
    Vector r; 
    //formula 
    //rx = ax + bx
    //ry = ay + by 
    //rz = az + bz 
    r.x = (a.y * b.z) - (a.z * b.y); //so subtract everything that doesnt have x
    r.y = (a.z * b.x) - (a.x * b.z); //subtract everything without y
    r.z = (a.x*b.y) - (a.y*b.x); //subtract everything without z
    r.used = 1; //set the flag in the struct to used
    r.name[0] = '\0'; //get rid of garbage in name
    return r; //return calculated vector 
}
