#include "Path.h"
#include "World.h"

Path::Path(GLuint texture, float x, float y, float z) : BaseObject(x, y, z) {
	this->texture = texture;
	this->index = 0;

	//Create a cube with 6 faces, similar to assignments.

	quad(0, 1, 5, 4, vec3(0.0, 0.0, 1.0)); // Front
	quad(1, 2, 6, 5, vec3(1.0, 0.0, 0.0)); // Right
    quad(2, 3, 7, 6, vec3(0.0, 0.0, -1.0)); // Back
	quad(3, 0, 4, 7, vec3(-1.0, 0.0, 0.0)); // Left
    quad(4, 5, 6, 7, vec3(0.0, 1.0, 0.0)); // Top
	quad(3, 2, 1, 0, vec3(0.0, -1.0, 0.0)); // Bottom

	for (int i = 0; i < numVertices; i++) {
		this->vertices.push_back(points[i]);
		this->normals.push_back(normal_pts[i]);
        this->textures.push_back(tex_coords[i]);
	}
}


Path::~Path() {
}


void Path::quad(int a, int b, int c, int d, vec3 normal) {

	float x = position.x;
	float y = position.y;
	float z = position.z;

	vec4 vertices[8] = {
        vec4(x - World::cellSize / 2, y - HEIGHT / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y - HEIGHT / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y - HEIGHT / 2, z - World::cellSize / 2, 1.0),
        vec4(x - World::cellSize / 2, y - HEIGHT / 2, z - World::cellSize / 2, 1.0),
        vec4(x - World::cellSize / 2, y + HEIGHT / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y + HEIGHT / 2, z + World::cellSize / 2, 1.0),
        vec4(x + World::cellSize / 2, y + HEIGHT / 2, z - World::cellSize / 2, 1.0),
        vec4(x - World::cellSize / 2, y + HEIGHT / 2, z - World::cellSize / 2, 1.0)
	};

	normal_pts[index] = normal;
	points[index] = vertices[a];
	tex_coords[index++] = vec2(0.0, 0.0);

	normal_pts[index] = normal;
	points[index] = vertices[b];
	tex_coords[index++] = vec2(0.0, 1.0);

	normal_pts[index] = normal;
	points[index] = vertices[c];
	tex_coords[index++] = vec2(1.0, 1.0);

	normal_pts[index] = normal;
	points[index] = vertices[a];
	tex_coords[index++] = vec2(0.0, 0.0);

	normal_pts[index] = normal;
	points[index] = vertices[c];
	tex_coords[index++] = vec2(1.0, 1.0);

	normal_pts[index] = normal;
	points[index] = vertices[d];
	tex_coords[index++] = vec2(1.0, 0.0);
}

void Path::draw(GLuint Model) {
	glBindVertexArray(this->vao);
    glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(Model, 1, GL_TRUE, this->model);
	glDrawArrays(GL_TRIANGLES, 0, this->numVertices);
}