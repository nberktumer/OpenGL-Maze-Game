#include "BaseObject.h"

BaseObject::BaseObject(float x, float y, float z) {
    this->position = vec3(x, y, z);
	this->index = -1;
    this->model = mat4();
}

BaseObject::~BaseObject() {
}

int BaseObject::getVectorIndex() {
	return this->index;
}

void BaseObject::setVectorIndex(int vectorIndex) {
	this->index = vectorIndex;
}

vector<vec4> BaseObject::getVertices() {
	return this->vertices;
}

vector<vec3> BaseObject::getNormals() {
	return this->normals;
}

mat4 BaseObject::getModel() {
	return this->model;
}

void BaseObject::populateVertices(vector<vec4> vertices, vector<vec3> normals) {
	for (int i = 0; i < vertices.size(); i++) {
		this->vertices.push_back(vertices.at(i));
	}
	for (int i = 0; i < normals.size(); i++) {
		this->normals.push_back(normals.at(i));
	}
}