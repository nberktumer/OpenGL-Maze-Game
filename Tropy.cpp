#include "Tropy.h"
#include "World.h"
#include <vector>

Tropy::Tropy(GLuint program, float x, float y, float z) : BaseObject(program, x, y, z) {
    // set the material properties (Goldish)
    this->useColor = true;
    this->material_ambient = vec4( 0.329412, 0.223529, 0.027451, 1.0 );
    this->material_diffuse = vec4( 0.5, 0.5, 0.0, 1.0 );
	this->material_specular = vec4( 0.992157, 0.941176, 0.807843, 1.0 );

    this->rotation.x = -90;

    this->ambient_product = World::light_ambient * material_ambient;
    this->diffuse_product = World::light_diffuse * material_diffuse;
    this->specular_product = World::light_specular * material_specular;

    // Load the 3D model file
    loadOBJ("tropy.obj", this->vertices, this->normals);
}

/**
 * Render the object
 */
void Tropy::draw(GLuint Model) {
    glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);
	glUniform1i(glGetUniformLocation(program, "UseColor"), 1);

    mat4 model = Translate(position) * RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z) * Scale(0.1, 0.1, 0.1) * this->model;

	glBindVertexArray(this->vao);
	glUniformMatrix4fv(Model, 1, GL_TRUE, model);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}