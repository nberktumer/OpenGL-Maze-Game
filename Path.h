#pragma once
#ifndef PATH_H
#define PATH_H
#include "BaseObject.h"

class Path : public BaseObject {
    public:
        Path(GLuint texture, float x, float y, float z);
        ~Path();
        void quad(int a, int b, int c, int d, vec3 normal);
        void draw(GLuint Model);
        static constexpr float HEIGHT = 0.1;
    private:
        static constexpr int numVertices = 36;

        vec4 points[numVertices];
        vec3 normal_pts[numVertices];
        vec2 tex_coords[numVertices];

        int index;
};

#endif
