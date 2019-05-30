#include "Camera.h"

Camera::Camera(GLuint View, vec3 eye, vec3 viewDirection, vec3 up) {
    this->eye = eye;
    this->viewDirection = viewDirection;
    this->up = up;

	// Initialize the camera
	mat4 view = LookAt(eye, eye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);
}

/**
 * Get the position of the camera
 */
vec3 Camera::getPosition() {
    return vec3(eye.x, eye.y, eye.z);
}

/**
 * Move the camera forward and backwards with the given amount value
 * Do not move if there is a wall
 * 
 * This function is taken from Jamie King's OpenGL tutorial
 * https://www.youtube.com/watch?v=7oNLw9Bct1k
 */
void Camera::moveForward(GLuint View, float amount, Boundry_t boundries) {
    // Do not move in Y-axis
	vec4 newEye = eye + amount * -viewDirection;

	const float cellSize = boundries.cellSize;
	const float leftBound = boundries.center.z - cellSize / 2;
	const float rightBound = boundries.center.z + cellSize / 2;
	const float bottomBound = boundries.center.x - cellSize / 2;
	const float topBound = boundries.center.x + cellSize / 2;

	if(
		(boundries.left == 1 && newEye.z <= leftBound)
		|| (boundries.right == 1 && newEye.z >= rightBound)
		|| (boundries.bottom == 1 && newEye.x <= bottomBound)
		|| (boundries.top == 1 && newEye.x >= topBound)
	) {
		return;
	}

	newEye.y = eye.y;
	eye = newEye;
	mat4 view = LookAt(newEye, newEye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);
}

/**
 * Move the camera left and right with the given amount value
 * Do not move if there is a wall
 * 
 * This function is taken from Jamie King's OpenGL tutorial
 * https://www.youtube.com/watch?v=7oNLw9Bct1k
 */
void Camera::moveRight(GLuint View, float amount, Boundry_t boundries) {
	vec4 newEye = eye + amount * cross(viewDirection, up);
	
	const float cellSize = boundries.cellSize;
	const float leftBound = boundries.center.z - cellSize / 2;
	const float rightBound = boundries.center.z + cellSize / 2;
	const float bottomBound = boundries.center.x - cellSize / 2;
	const float topBound = boundries.center.x + cellSize / 2;

	if(
		(boundries.left == 1 && newEye.z <= leftBound)
		|| (boundries.right == 1 && newEye.z >= rightBound)
		|| (boundries.bottom == 1 && newEye.x <= bottomBound)
		|| (boundries.top == 1 && newEye.x >= topBound)
	) {
		return;
	}

	newEye.y = eye.y;
	eye = newEye;
	mat4 view = LookAt(newEye, newEye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);

}

/**
 * Rotate the camera with the given displacement vector
 * 
 * This function is taken from Jamie King's OpenGL tutorial
 * https://www.youtube.com/watch?v=7oNLw9Bct1k
 */
void Camera::rotate(GLuint View, vec2 displacement) {
    glm::vec3 vector = glm::vec3(viewDirection.x, viewDirection.y, viewDirection.z);
	vector = glm::mat3(glm::rotate(-displacement.x * (GLfloat)0.006, glm::vec3(up.x, up.y, up.z))) * vector;

	glm::vec3 rotateAround = glm::cross(vector, glm::vec3(up.x, up.y, up.z));
	vector = glm::mat3(glm::rotate(-displacement.y * (GLfloat)0.006, rotateAround)) * vector;
	viewDirection = vec4(vector.x, vector.y, vector.z, 0.0f);
	
	mat4 view = LookAt(eye, eye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);
}