#include "model.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dependencies/include/GL/glew.h"

#define VERTEX_LIMIT 2000

//DynamicArray* loadOBJ(const char* filename);
//void processVertex(DynamicArray* vertices, char* vertexData[3], Vertex v[], Vertex vt[], Vertex vn[]);

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
        for (int i = 1; i < 4; ++i) {
            words[i] = strtok(NULL, " ");
        }

        if (strcmp(words[0], "v") == 0) {
            v[v_count].x = atof(words[1]);
            v[v_count].y = atof(words[2]);
            v[v_count].z = atof(words[3]);
            v_count++;
        } else if (strcmp(words[0], "vt") == 0) {
            vt[vt_count].x = atof(words[1]);
            vt[vt_count].y = atof(words[2]);
            vt_count++;
        } else if (strcmp(words[0], "vn") == 0) {
            vn[vn_count].x = atof(words[1]);
            vn[vn_count].y = atof(words[2]);
            vn[vn_count].z = atof(words[3]);
            vn_count++;
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

            processVertex(vertices, v1, v, vt, vn);
            processVertex(vertices, v2, v, vt, vn);
            processVertex(vertices, v3, v, vt, vn);
        }
    }
    fclose(fp);
    if (line) {
        free(line);
    }

    return vertices;
}