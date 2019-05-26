#pragma once
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "Angel.h"
#include <vector>

using namespace std;

class BaseObject {
    public:
        mat4 model;
        GLuint vao;
        GLuint buffer;
        GLuint texture;
        vector<vec4> vertices;
        vector<vec3> normals;
        vector<vec2> textures;
        vec3 position;

        BaseObject(float x, float y, float z);
        ~BaseObject();
        
        virtual void draw(GLuint Model) = 0;

        int getVectorIndex();
        void setVectorIndex(int vectorIndex);
        vector<vec4> getVertices();
        vector<vec3> getNormals();
        vector<vec2> getTextures();
        mat4 getModel();
    private:
        int index;
};

#endif