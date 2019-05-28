#include "BaseObject.h"

#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstring>

BaseObject::BaseObject(GLuint program, float x, float y, float z) {
	this->program = program;
    position = vec3(x, y, z);
	rotation = vec3(0, 0, 0);
	index = -1;
    model = mat4();
}

BaseObject::~BaseObject() {
}

int BaseObject::getVectorIndex() {
	return index;
}

void BaseObject::setVectorIndex(int vectorIndex) {
	index = vectorIndex;
}

vector<vec4> BaseObject::getVertices() {
	return vertices;
}

vector<vec3> BaseObject::getNormals() {
	return normals;
}

vector<vec2> BaseObject::getTextures() {
	return textures;
}

mat4 BaseObject::getModel() {
	return model;
}

// .obj loader taken from https://github.com/huamulan/OpenGL-tutorial/blob/master/common/objloader.cpp
void BaseObject::loadOBJ(const char * path,	vector<vec4> &vertices,	vector<vec3> &normals) {
	vector<int> vertexIndices, normalIndices;
	vector<vec4> temp_vertices; 
	vector<vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if(file == NULL){
		printf("Could not read the file!\n");
		return;
	}

	while(true) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		
		if (strcmp(lineHeader, "v") == 0) {
			vec4 vertex;
			vertex.w = 1.0;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		} else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		} else if (strcmp(lineHeader, "f") == 0) {
			string vertex1, vertex2, vertex3;
			int vertexIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d//%d %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2], &vertexIndex[3], &normalIndex[3] );
			if (matches != 8){
				printf("File could not be parsed!\n");
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[3]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[2]);
			normalIndices.push_back(normalIndex[3]);
		} else {
			char buff[1000];
			fgets(buff, 1000, file);
		}
	}

	// For each vertex of each triangle
	for(int i = 0; i < vertexIndices.size(); i++){
		// Get the indices of its attributes
		int vertexIndex = vertexIndices[i];
		int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		vec4 vertex = temp_vertices[ vertexIndex-1 ];
		vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		vertices.push_back(vertex);
		normals .push_back(normal);
	}
}