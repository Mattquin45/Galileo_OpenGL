#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "dependencies/include/GL/glew.h"
#include "dependencies/include/GLFW/glfw3.h"

#include "graphics.h"
#include "shader.h"
#include "model.h"
#include "galileo.h"
//#include "camera.h"


//declare an array of objects to simulate
GalileoObject objects[3];

//settings of window for GLEW
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main(){
    //Object = mass, position, velocity, acceleration, drag coefficient, cross sectional area
    //each variable has different value arrays because of X, Y, Z axis
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



    GLFWwindow* window;

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Verlet Integration", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
}