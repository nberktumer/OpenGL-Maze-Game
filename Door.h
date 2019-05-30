#pragma once
#ifndef DOOR_H
#define DOOR_H
#include "BaseObject.h"

class Door : public BaseObject {
    public:
        Door(GLuint program, GLuint texture, float x, float y, float z);
        void quad(int a, int b, int c, int d, vec3 normal);
        void draw(GLuint Model);
        static constexpr float HEIGHT = 6.0;
    private:
        static constexpr int numVertices = 36;

        vec4 points[numVertices];
        vec3 normal_pts[numVertices];
        vec2 tex_coords[numVertices];
        int index;
};

#endif
