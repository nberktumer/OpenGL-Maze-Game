#pragma once
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "Angel.h"
#include <vector>

using namespace std;

class BaseObject {
    public:
        mat4 model;
        vec4 color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        GLuint vao;
        GLuint buffer;
        vector<vec4> vertices;
        vector<vec3> normals;
        vec3 position;

        BaseObject(float x, float y, float z);
        ~BaseObject();
        
        virtual void draw(GLint modelLoc, GLint colorLoc) = 0;

        int getVectorIndex();
        void setVectorIndex(int vectorIndex);
        vector<vec4> getVertices();
        vector<vec3> getNormals();
        mat4 getModel();
        void populateVertices(vector<vec4> vertices, vector<vec3> normals);
    private:
        int index;
};

#endif