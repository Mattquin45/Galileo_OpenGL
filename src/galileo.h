#include "mathc.h"

typedef struct {
    //VEC_SIZE since we can switch between 2D and 3D easily
    float mass;
    float position[VEC3_SIZE];
    float velocity[VEC3_SIZE];
    float acceleration[VEC3_SIZE];
    float drag_coefficient;
} GalileoObject;