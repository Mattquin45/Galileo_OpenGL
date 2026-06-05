#ifndef SHADER_H
#define SHADER_H

unsigned int createShader(const char* vertexFile, const char* fragmentFile);

void detachShader();

void destroyShader(unsigned int shaderID);

#endif