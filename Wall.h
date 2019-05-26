#pragma once
#ifndef WALL_H
#define WALL_H
#include "BaseObject.h"

class Wall : public BaseObject {
    public:
        Wall(GLuint texture, float x, float y, float z);
        ~Wall();
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
