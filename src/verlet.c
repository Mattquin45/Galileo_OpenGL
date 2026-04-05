#include "verlet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "galileo.h"

#define GRAVITY -15.0f
#define THREAD_COUNT 8
//Controlling the air resistance wanted
#define AIR_DENSITY 1.225f
//Objects we want to test the air resistance on


// ===============================
// Gravity simulation with Verlet integration
// ===============================  
void applyForces(GalileoObject* galileoObjects, int size)
{
    for (int i = 0; i < size; i++) {
        //pulls particles downwards on every Y axis frame
        //calls from the VerletObject struct and the acceleration vector uses the Y axis
        //which is 0, 1, 2 for X, Y, Z respectively
        float drag = 0.5f * AIR_DENSITY * galileoObjects[i].velocity[1] * galileoObjects[i].velocity[1] * galileoObjects[i].drag_coefficient * galileoObjects[i].cross_sectional_area; 
        // Calculate the net force on the object
        float net_force = (galileoObjects[i].mass * GRAVITY) - drag;
        // Update the object's acceleration based on the net force
        // A = g * m - drag / m  = g - drag/m
        float acceleration = net_force / galileoObjects[i].mass;

        galileoObjects[i].acceleration[1] += acceleration;

        //galileoObjects[i].acceleration[1] = acceleration;
        //float speed = objects[i].acceleration[1];
        //speed += GRAVITY;
        
    }
}



#define DIMENSION 58 // CONTAINER_RADIUS / VERLET_RADIUS + 5
#define MAX_PER_CELL 4
VerletObject* grid[DIMENSION][DIMENSION][DIMENSION][MAX_PER_CELL];

pthread_t threads[THREAD_COUNT];
int thread_ids[THREAD_COUNT];


void applyConstraints(GalileoObject* objects, int size, mfloat_t* containerPosition)
{
    // ========= Floor =========
     for (int i = 0; i < size; i++) {
         GalileoObject* obj = &(objects[i]);
         if (obj->position[1] <= 0) {
                obj->position[1] = 0;
                // simple bounce with damping
                obj->velocity[1] *= -0.5f; 
             
        }
     }

}
// ===============================
//MAIN SIMULATION FUNCTIONS
// ================================
void updatePositions(GalileoObject* objects, int size, float dt)
{
    for (int i = 0; i < size; i++) {
        GalileoObject* obj = &(objects[i]);
        mfloat_t disp[VEC3_SIZE];
        
        //since we know the acceleration, we can just then update the velocity and position of the object using the acceleration
        obj -> velocity[1] += obj -> acceleration[1] * dt;
        obj->position[1] += obj->velocity[1] * dt;
        // Reset acceleration for the next frame
        obj->acceleration[1] = 0.0f;
        
    }
}

void addForce(VerletObject* objects, int size, mfloat_t* center, float strength)
{
    for (int i = 0; i < size; i++) {
        VerletObject* obj = &(objects[i]);
        mfloat_t disp[VEC3_SIZE];
        vec3_subtract(disp, obj->current, center);
        mfloat_t dist = vec3_length(disp);
        if (dist > 0) {
            mfloat_t norm[VEC3_SIZE];
            vec3_divide_f(norm, disp, dist);
            vec3_multiply_f(norm, norm, strength);
            vec3_add(obj->acceleration, obj->acceleration, norm);
        }
    }
}
