#include "model.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dependencies/include/GL/glew.h"

#define VERTEX_LIMIT 2000

DynamicArray* loadOBJ(const char* filename);
void processVertex(DynamicArray* vertices, char* vertexData[3], Vertex v[], Vertex vt[], Vertex vn[]);

// creates a mesh object from a file (the geometry)
Mesh *createMesh(const char *filename, bool instanced) {

  // Load the specific file and store it in a dynamic array
  // it is then reflected on dArray -> array/ total count is dArray->size
    DynamicArray* dArray = loadOBJ(filename);

    // allocates the mesh object on the heap
    Mesh *mesh = malloc(sizeof(Mesh));
    // assigns the vertices to the mesh object
    mesh->vertices = dArray->array;
    // calculates the number of vertices (each vertex has 8 floats)
    mesh->numVertices = dArray->size / STRIDE;

    // Create our Vertex Buffer and Vertex Array Objects
    // this is necessary because the GPU needs to know how to process the vertices and pixels of the model
    // it remembers how the vertex data is organized so it can process with ease on OpenGL
    glGenVertexArrays(1, &(mesh->VAO));
    glBindVertexArray(mesh->VAO);

    //creates a buffer object and allocates memory for it on the GPU
    glGenBuffers(1, &(mesh->VBO));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    // it then activates the buffer object and binds it to the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    // this then uploads the vertex data to the GPU and tells it how to process the vertices and pixels of the model from the CPU to the GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * STRIDE * mesh->numVertices, mesh->vertices, GL_STATIC_DRAW);

    // Position
    //this is the attribute slot of where it tells the GPU where to find the vertex data in the buffer object
    glEnableVertexAttribArray(0);
    //format then releases the 3 floats of position data and then jumps 32 bytes to the next vertex data and then repeats the process
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)0);
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)12);
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (void*)24);

    if (instanced) {
        // Position
        glGenBuffers(1, &(mesh->positionVBO));
        glBindBuffer(GL_ARRAY_BUFFER, mesh->positionVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * INSTANCE_STRIDE * MAX_INSTANCES, NULL, GL_STREAM_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, INSTANCE_STRIDE * sizeof(float), (void*)0);
        glVertexAttribDivisor(3, 1);

        // Velocity
        glGenBuffers(1, &(mesh->velocityVBO));
        glBindBuffer(GL_ARRAY_BUFFER, mesh->velocityVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * MAX_INSTANCES, NULL, GL_STREAM_DRAW);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
        glVertexAttribDivisor(4, 1);
    }

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return mesh;
}


DynamicArray *loadOBJ(const char *filename) {

  // allocates the vertices on the heap
  // this grabs all positions
    Vertex v[VERTEX_LIMIT];
    // allocates the texture coordinates on the heap
    Vertex vt[VERTEX_LIMIT];
    // allocates the normal coordinates on the heap
    Vertex vn[VERTEX_LIMIT];

    // counts the number of positions
    int v_count = 0;
    // counts the number of texture coordinates
    int vt_count = 0;
    // counts the number of normals
    int vn_count = 0;

    // allocates the dynamic array on the heap
    // the final output for the OpenGL shader program
    DynamicArray* vertices = malloc(sizeof(DynamicArray));
    // initializes the dynamic array
    //uses the initialize function to set the dynamic array's size to 0, 
    // capacity to 160, and allocates memory for the array of floats
    initialize(vertices, 160);

    // opens the file
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    //reads the OBJ file line by line so it is able to tokenize it into
    // positions, texture coordinates, and normals
    //when EOF is reached it returns -1 and the loop ends
    // getline what it does is that it uses line as a buffer count so
    // it can read lines of any length and it will automatically resize 
    // the buffer as needed
    // len keeps track of the size of the buffer of the line being read
    // fp opens the file and passes it to getline to read the lines of the file
    while ((read = getline(&line, &len, fp)) != -1) {
        char* words[4];
        //tokenization of the line into words
        // the first word is the type of data (v, vt, vn, f)
        words[0] = strtok(line, " ");

        // this is then for the data that follows the the type of first word
        // given that the first word is the type of data, the next three words are the actual data
        for (int i = 1; i < 4; ++i) {
            words[i] = strtok(NULL, " ");
        }

        // this data then gets processed and stored depending on the type of data it is
        // this is for the position of the vertex
        // the structure of the process is that it uses an array of data type of the vertex
        // then it stores it to that array and it increments the count of the variable correlated with the data

        //
        if (strcmp(words[0], "v") == 0) {
            v[v_count].x = atof(words[1]);
            v[v_count].y = atof(words[2]);
            v[v_count].z = atof(words[3]);
            v_count++;

        // this is for the texture image on the vertex
        } else if (strcmp(words[0], "vt") == 0) {
            vt[vt_count].x = atof(words[1]);
            vt[vt_count].y = atof(words[2]);
            vt_count++;

        // this is for the normal surface face vector of the vertex
        } else if (strcmp(words[0], "vn") == 0) {
            vn[vn_count].x = atof(words[1]);
            vn[vn_count].y = atof(words[2]);
            vn[vn_count].z = atof(words[3]);
            vn_count++;

        // this then processes how the vertex is connected to the other vertices in the model
        // this processes the 3 corners fo the model and then it uses the 
        // shape v, vt, vn to process the vertex data and store it in the dynamic array
        } else if (strcmp(words[0], "f") == 0) {
            char* v1[3];
            char* v2[3];
            char* v3[3];

            v1[0] = strtok(words[1], "/");
            v1[1] = strtok(NULL, "/");
            v1[2] = strtok(NULL, "/");
            v2[0] = strtok(words[2], "/");
            v2[1] = strtok(NULL, "/");
            v2[2] = strtok(NULL, "/");
            v3[0] = strtok(words[3], "/");
            v3[1] = strtok(NULL, "/");
            v3[2] = strtok(NULL, "/");

            // after that it then processes the vertex data and stores it in the dynamic array
            processVertex(vertices, v1, v, vt, vn);
            processVertex(vertices, v2, v, vt, vn);
            processVertex(vertices, v3, v, vt, vn);
        }
    }
    fclose(fp);
    if (line) {
        free(line);
    }

    //returns vertices which are ready to be used in the OpenGL shader program
    return vertices;
}

void processVertex(DynamicArray* vertices, char* vertexData[3], Vertex v[], Vertex vt[], Vertex vn[])
{

    // the reason why it subtracts from 1 is because obj files 
    // are 1 indexed and C is 0 indexed
    // this is for the specific corners of the triangle

    int vertex_ptr = atoi(vertexData[0]) - 1;
    int texture_ptr = atoi(vertexData[1]) - 1;
    int normal_ptr = atoi(vertexData[2]) - 1;

    // after that, then it pushes the specific vertex data to the dynamic array in the order of position, normal, and texture coordinates
    push(vertices, v[vertex_ptr].x);
    push(vertices, v[vertex_ptr].y);
    push(vertices, v[vertex_ptr].z);

    push(vertices, vn[normal_ptr].x);
    push(vertices, vn[normal_ptr].y);
    push(vertices, vn[normal_ptr].z);

    push(vertices, vt[texture_ptr].x);
    push(vertices, vt[texture_ptr].y);
}