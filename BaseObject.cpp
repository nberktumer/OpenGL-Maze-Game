#include "BaseObject.h"

BaseObject::BaseObject(float x, float y, float z) {
    position = vec3(x, y, z);
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