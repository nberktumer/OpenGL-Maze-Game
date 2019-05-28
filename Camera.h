#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "BaseObject.h"
#include "Boundry.h"
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

class Camera {
    public:
        Camera(GLuint View, vec3 eye, vec3 viewDirection, vec3 up);
        ~Camera();
        vec3 getPosition();
        void moveForward(GLuint View, float amount, Boundry_t boundries);
        void moveRight(GLuint View, float amount, Boundry_t boundries);
        void rotate(GLuint View, vec2 displacement);
    private:
        vec4 eye; // The position of the camera
        vec4 viewDirection; // Camera's direction.
        vec4 up; // Up vector of eye.
};

#endif
