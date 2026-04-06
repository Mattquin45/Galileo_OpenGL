#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <galileo.h>


//declare an array of objects to simulate
GalileoObject objects[3];

int main(){
    //Object = mass, position, velocity, acceleration, drag coefficient, cross sectional area
    //Object 1: A feather
    objects[0].mass = 0.01f;
    objects[0].position[0] = 0.0f;
    objects[0].position[1] = 20.0f;
    objects[0].position[2] = 0.0f;
    objects[0].velocity[0] = 0.0f;
    objects[0].velocity[1] = 0.0f;
    objects[0].velocity[2] = 0.0f;
    objects[0].acceleration[0] = 0.0f;
    objects[0].acceleration[1] = 0.0f;
    objects[0].acceleration[2] = 0.0f;
    // Approximate drag coefficient for a feather
    objects[0].drag_coefficient = 1.5f; 
    // Approximate drag coefficient for a feather
    objects[0].cross_sectional_area = 0.01f;

    //Object 2: A camera
    objects[1].mass = 1.7f;
    objects[1].position[0] = 0.0f;
    objects[1].position[1] = 20.0f;
    objects[1].position[2] = 0.0f;
    objects[1].velocity[0] = 0.0f;
    objects[1].velocity[1] = 0.0f;
    objects[1].velocity[2] = 0.0f;
    objects[1].acceleration[0] = 0.0f;
    objects[1].acceleration[1] = 0.0f;
    objects[1].acceleration[2] = 0.0f;
    // Approximate drag coefficient for a camera
    objects[1].drag_coefficient = 0.8f;
    // Approximate drag coefficient for a camera
    objects[1].cross_sectional_area = 0.05f;


}