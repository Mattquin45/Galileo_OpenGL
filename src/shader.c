#include <stdlib.h>
#include <stdio.h>
#include "shader.h"
#include "util.h"

#include "dependencies/include/GL/glew.h"

//===========================================
// Shader Creation and Management
//===========================================

// both are needed to create a shader program that links the vertex(transforms vertices to 3D)
// and fragment shader (colors the pixels) together

unsigned int createShader(const char* vertexFile, const char* fragmentFile)
{

    GLint success = 0;
    GLint logSize = 0;

    // Create a shader object and compile it during runtime
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Read the vertex shader file
    const char* vertexShaderSource = readFile(vertexFile);
    //attaches the shader source to the shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //compiles the shader
    glCompileShader(vertexShader);
    //checks if the shader compiled successfully

    //checks if the shader compiled successfully
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //if the compilation of the shader fails
    if (success == GL_FALSE) {
        //it gets the query log size for the vertex shader
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar infoLog[logSize];
        //gets the info log for the vertex shader
        glGetShaderInfoLog(vertexShader, logSize, &logSize, infoLog);
        //deletes the shader object
        glDeleteShader(vertexShader);
        //prints the info log for the vertex shader(error message)
        printf("Vertex Shader: %s\n", infoLog);
    }

    // Perform the same steps for the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = readFile(fragmentFile);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
        GLchar infoLog[logSize];
        glGetShaderInfoLog(fragmentShader, logSize, &logSize, infoLog);
        glDeleteShader(fragmentShader);
        printf("Fragment Shader: %s\n", infoLog);
    }

    // Create a shader program and link the two shader steps together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Make sure to cleanup the individual shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Return the program
    return shaderProgram;
}

void detachShader()
{
    glUseProgram(0);
}

void destroyShader(unsigned int shaderID)
{
    glDeleteProgram(shaderID);
}