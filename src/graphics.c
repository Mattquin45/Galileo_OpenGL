#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dependencies/include/GL/glew.h"

#include "graphics.h"

// This actually draws the mesh to the screen by setting up the matrices and drawing the mesh
void drawMesh(Mesh *mesh, unsigned int shaderID, GLenum mode,
              mfloat_t *position, mfloat_t *rotation, mfloat_t scale) {
  // this sets up the different things about the mesh object
  // position, rotation, and scaling
    mfloat_t scaling[VEC3_SIZE] = { scale, scale, scale };

    struct {
        mfloat_t position[MAT4_SIZE];
        mfloat_t rotation[MAT4_SIZE];
        mfloat_t scaling[MAT4_SIZE];
        mfloat_t model[MAT4_SIZE];
    } matrices;

    /* Position */
    // this sets the position of the mesh object in the world
    mat4_identity(matrices.position);
    mat4_translation(matrices.position, matrices.position, position);

    /* Rotation */
    // this sets the rotation of the mesh object in the world
    mat4_identity(matrices.rotation);
    mat4_from_eulers(matrices.rotation, rotation);

    /* Scaling */
    // this sets the scaling of the mesh object in the world
    mat4_identity(matrices.scaling);
    mat4_scaling(matrices.scaling, matrices.scaling, scaling);

    /* Model matrix */
    // this combines the position, rotation, and scaling into a single matrix
    // this then tells the GPU everything on how to draw the mesh object
    mat4_multiply(matrices.model, matrices.rotation, matrices.scaling);
    mat4_multiply(matrices.model, matrices.position, matrices.model);


    // this uses the shader program to draw the mesh object
    glUseProgram(shaderID);
    // this sets the model matrix for the mesh object
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE,
                       matrices.model);
    

    

    // this sets up the projection matrix
    mfloat_t projection[MAT4_SIZE];
    // this sets the projection matrix for the mesh object
    // this then tells the GPU how to project the mesh object onto the screen
    // the format is mat4_perspective(field_of_view, screen aspect ratio, near, far);
    mat4_perspective(projection, to_radians(45.0), (float)1280 / (float)720, 0.1, 100.0);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"),
        1, GL_FALSE, projection);


    // the way it binds the vertex data together is by using a struct variable called VAO (Vertex Array Object)
    // this saves the vertex data on how it is organized from model.h and then tells the GPU how to process the vertices and pixels of the model
    // VAO is then talking to glBindVertexArray saying, to use the struct data to read the vertex data and then draw the mesh object
    glBindVertexArray(mesh->VAO);


    // this then draws the mesh object to the screen by using the vertex data and the shader program
    // the format is glDrawArrays(mode, first, count);
    // mode is the type of primitive to draw (GL_TRIANGLES, GL_LINES, etc)
    glDrawArrays(mode, 0, mesh->numVertices);

    // this then frees the shader program and the VAO so that it can be used again for the next mesh object
    glUseProgram(0);
    glBindVertexArray(0);
}


/*
void drawInstanced(Mesh* mesh, unsigned int shaderID, GLenum mode, int num, mfloat_t scale)
{
    glUseProgram(shaderID);

    mfloat_t projection[MAT4_SIZE];

    mat4_perspective(projection, to_radians(45.0), (float)1280 / (float)720, 0.1, 100.0);

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"),
        1, GL_FALSE, projection);

    glUniform1f(glGetUniformLocation(shaderID, "scale"), scale);

    glBindVertexArray(mesh->VAO);

    glDrawArraysInstanced(mode, 0, mesh->numVertices, num);

    glUseProgram(0);

    glBindVertexArray(0);
}
*/
