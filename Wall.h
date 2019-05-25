#pragma once
#ifndef WALL_h
#define WALL_H
#include "BaseObject.h"

class Wall : public BaseObject {
    public:
        Wall(float x, float y, float z);
        ~Wall();
        void quad(int i1, int i2, int i3, int i4, vec3 normal);
        void draw(GLint modelLoc, GLint colorLoc);
    private:
        static constexpr int numVertices = 36;
        static constexpr float height = 4.0;

        vec4 cubePoints[numVertices];
        vec3 cubeNormals[numVertices];
        vec3 position;

        int cubeVertexIndex;
};

#endif
