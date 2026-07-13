#include "camera.h"
#include "stdlib.h"

Camera* createCamera(mfloat_t *position){
    Camera* camera = malloc(sizeof(Camera));

    // this assigns the position of the camera to the position passed in
    vec3_assign(camera->position, position);

    camera->yaw = -90.0f;
    camera->pitch = 0.0f;

    updateVectors(camera);

    return camera;
}

void updateVectors(Camera *camera) {
  // this updates the forwards vector of the camera
  // normalization is a part of this because it makes the vector have a length
  // of 1
  // this allows for the camera to move in a correct speed
    vec3(camera->forwards,
        MCOS(MRADIANS(camera->yaw)) * MCOS(MRADIANS(camera->pitch)),
        MSIN(MRADIANS(camera->pitch)),
        MSIN(MRADIANS(camera->yaw)) * MCOS(MRADIANS(camera->pitch)));
    vec3_normalize(camera->forwards, camera->forwards);
    vec3_cross(camera->right, camera->forwards, (mfloat_t[])GLOBAL_UP);
    vec3_normalize(camera->right, camera->right);
    vec3_cross(camera->up, camera->right, camera->forwards);
    vec3_normalize(camera->up, camera->up);
}

mfloat_t* createViewMatrix(mfloat_t* viewMatrix, Camera* camera)
{
    // this updates the vectors of the camera
    updateVectors(camera);
    // this creates a new target vector
    mfloat_t target[VEC3_SIZE];
    vec3_add(target, camera->position, camera->forwards);

    //updates the view matrix of the camera by using the look at function
    mat4_look_at(viewMatrix, camera->position, target, camera->up);
    return viewMatrix;
}