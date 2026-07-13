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


    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //MAC OSX compatibility
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // creates a window with the specified width, height, and title. The last two parameters are for monitor and share, which are set to NULL for a simple window.
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "galileo simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // ataches the OpenGL context to the window, allowing OpenGL commands to be executed in that window.
    glfwMakeContextCurrent(window);

    /* Set up a callback function for when the window is resized */
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSwapInterval(1);
    
    /* Initialize GLEW */
    glewInit();

    /* OpenGL Settings */
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClearStencil(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(3.0);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //this show the actual frame of the window and then polls for events like keyboard and mouse input
        glfwSwapBuffers(window);
        glfwPollEvents();


        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);   
        }
        

    }

    glfwTerminate();
    return 0;
}