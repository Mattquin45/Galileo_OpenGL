//Doesn't allow the header to be included multiple times
#ifndef __GALILEO_H__
#define __GALILEO_H__

#include "mathc.h"

//Controlling the air resistance wanted
#define AIR_DENSITY 1.225f


typedef struct {
    //VEC_SIZE since we can switch between 2D and 3D easily
    float mass;
    float position[VEC3_SIZE];
    float velocity[VEC3_SIZE];
    float acceleration[VEC3_SIZE];
    //shape of the object
    float drag_coefficient;
    //area of the object
    float cross_sectional_area;
} GalileoObject;

//Simulates gravity by updating the position by finding the difference
//between the current and previous position, then applying the acceleration to the velocity and updating the position accordingly
void updatePositions(GalileoObject* objects, int size, float dt);
//Makes OpenGl create an actual floor for the objects stop with manipulating the positions 
//and velocities of the objects when they hit the floor
void applyConstraints(GalileoObject* objects, int size, mfloat_t* containerPosition);
//Applies Galileo's experiment of Objects with different masses falling at the same rate
//but with air resistance
void applyForces(GalileoObject *galileoObjects, int size);

#endif 