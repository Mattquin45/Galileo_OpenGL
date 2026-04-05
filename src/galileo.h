#include "mathc.h"

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