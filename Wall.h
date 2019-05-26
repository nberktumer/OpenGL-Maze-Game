#pragma once
#ifndef WALL_H
#define WALL_H
#include "BaseObject.h"

class Wall : public BaseObject {
    public:
        Wall(float x, float y, float z);
        ~Wall();
        void quad(int i1, int i2, int i3, int i4, vec3 normal);
        void draw(GLint modelLoc, GLint colorLoc);
        static constexpr float HEIGHT = 4.0;
    private:
        static constexpr int numVertices = 36;

        vec4 cubePoints[numVertices];
        vec3 cubeNormals[numVertices];

        int cubeVertexIndex;
};

#endif
