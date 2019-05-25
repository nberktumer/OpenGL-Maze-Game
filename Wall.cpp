#include "Wall.h"
#include "World.h"

Wall::Wall(float x, float y, float z) : BaseObject() {
	this->position = vec3(x, y, z);
	this->cubeVertexIndex = 0;
	this->color = vec4(0.0f,1.0f,0.0f,1.0f);

	//Create a cube with 6 faces, similar to assignments.

	quad(0, 1, 5, 4, vec3(0.0, 0.0, 1.0)); // Front
	quad(1, 2, 6, 5, vec3(1.0, 0.0, 0.0)); // Right
    quad(2, 3, 7, 6, vec3(0.0, 0.0, -1.0)); // Back
	quad(3, 0, 4, 7, vec3(-1.0, 0.0, 0.0)); // Left
    quad(4, 5, 6, 7, vec3(0.0, 1.0, 0.0)); // Top
	quad(3, 2, 1, 0, vec3(0.0, -1.0, 0.0)); // Bottom

	for (int i = 0; i < numVertices; i++) {
		this->vertices.push_back(cubePoints[i]);
		this->normals.push_back(cubeNormals[i]);
	}
}


Wall::~Wall() {
}


void Wall::quad(int i1, int i2, int i3, int i4, vec3 normal) {

	float x = position.x;
	float y = position.y;
	float z = position.z;

	vec4 vertices[8] = {
        vec4(x - World::cellSize / 2, y - height / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y - height / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y - height / 2, z - World::cellSize / 2, 1.0),
        vec4(x - World::cellSize / 2, y - height / 2, z - World::cellSize / 2, 1.0),
        vec4(x - World::cellSize / 2, y + height / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y + height / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y + height / 2, z - World::cellSize / 2, 1.0),
        vec4(x - World::cellSize / 2, y + height / 2, z - World::cellSize / 2, 1.0)
	};

	cubeNormals[cubeVertexIndex] = normal;
	cubePoints[cubeVertexIndex++] = vertices[i1];
	cubeNormals[cubeVertexIndex] = normal;
	cubePoints[cubeVertexIndex++] = vertices[i2];
	cubeNormals[cubeVertexIndex] = normal;
	cubePoints[cubeVertexIndex++] = vertices[i3];

	cubeNormals[cubeVertexIndex] = normal;
	cubePoints[cubeVertexIndex++] = vertices[i3];
	cubeNormals[cubeVertexIndex] = normal;
	cubePoints[cubeVertexIndex++] = vertices[i4];
	cubeNormals[cubeVertexIndex] = normal;
	cubePoints[cubeVertexIndex++] = vertices[i1];
}

void Wall::draw(GLint Model, GLint Color) {
	glBindVertexArray(this->vao);
	glUniformMatrix4fv(Model, 1, GL_TRUE, this->model);
	glUniform4fv(Color, 1, this->color);
	glDrawArrays(GL_TRIANGLES, 0, this->numVertices);
}