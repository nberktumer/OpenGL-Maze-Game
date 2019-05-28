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
        vec3 rotation;
        GLuint program;

        BaseObject(GLuint program, float x, float y, float z);
        ~BaseObject();
        
        virtual void draw(GLuint Model) = 0;

        int getVectorIndex();
        void setVectorIndex(int vectorIndex);
        vector<vec4> getVertices();
        vector<vec3> getNormals();
        vector<vec2> getTextures();
        void loadOBJ(const char * path,	vector<vec4> &vertices,	vector<vec3> &normals);
        mat4 getModel();
        bool useColor = false;
        vec4 material_ambient;
        vec4 material_diffuse;
        vec4 material_specular;
        float material_shininess = 256.0;
        vec4 ambient_product;
        vec4 diffuse_product;
        vec4 specular_product;
    private:
        int index;

};

#endif