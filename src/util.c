#include <stdio.h>
#include <stdlib.h>

#include "util.h"

//A utility that reads a file and returns its content as a string
char* readFile(const char* filename)
{
    FILE* fp;
    long size = 0;
    char* content;

    /* Read File to get size */
    //opens file in binary mode to give exact byte count
    fp = fopen(filename, "rb");
    //Check if file was opened successfully
    if (fp == NULL) {
        printf("Couldn't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    //moves the file pointer to the end to get the size of the file
    fseek(fp, 0L, SEEK_END);
    //adds 1 to the size to account for the null terminator
    size = ftell(fp) + 1;
    //closes the file after getting the size
    fclose(fp);

    /* Read File for Content */
    //opens file in text mode(r) to read the content as a string
    //for shaders
    fp = fopen(filename, "r");
    //allocates enough memory to hold the content of the file
    content = malloc(size);
    //reads the content of the file into the allocated memory
    fread(content, 1, size - 1, fp);
    //adds the null terminator at the end of the content string
    content[size - 1] = '\0';
    //closes the file after reading the content
    fclose(fp);

    return content;
}