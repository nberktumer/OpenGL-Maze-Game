#pragma once
#ifndef PATH_H
#define PATH_H
#include "BaseObject.h"

class Path : public BaseObject {
    public:
        Path(float x, float y, float z);
        ~Path();
        void quad(int i1, int i2, int i3, int i4, vec3 normal);
        void draw(GLint modelLoc, GLint colorLoc);
        static constexpr float HEIGHT = 0.1;
    private:
        static constexpr int numVertices = 36;

        vec4 cubePoints[numVertices];
        vec3 cubeNormals[numVertices];

        int cubeVertexIndex;
};

#endif
