//
//  Display a rotating cube, revisited
//
#define GLM_ENABLE_EXPERIMENTAL

#include "Angel.h"
#include <stdlib.h>
#include <vector>
#include "World.h"
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

using namespace std;

typedef vec4 color4;
typedef vec4 point4;

enum Axis {
    Xaxis, Yaxis, Zaxis
};

void quad(int a, int b, int c, int d, color4 color);

void cube(int x, int y, int z);

void rubikscube(void);

void init(void);

void display(void);

void reshape(int w, int h);

void idle(void);

void animationTimer(int arg);

void keyboard(unsigned char key, int x, int y);

int main(int argc, char **argv);

vec4 eye = vec4(0.0, 0.0, 0.0, 1.0f); //The position the camera stands on.
vec4 viewDirection = vec4(0.0f, 0.0f, -1.0f, 0.0f); // the direction vector that the camera looks towards.
vec4 up = vec4(0.0, 1.0, 0.0, 0.0); //The up vector of eye.
vec2 previousMousePosition = vec2(0, 0);

const color4 cube_colors[] = {
        color4(1.0, 0.0, 0.0, 1.0),  // red
        color4(1.0, 1.0, 0.0, 1.0),  // yellow
        color4(0.0, 1.0, 0.0, 1.0),  // green
        color4(0.0, 0.0, 1.0, 1.0),  // blue
        color4(1.0, 0.0, 1.0, 1.0),  // magenta
        color4(0.0, 1.0, 1.0, 1.0),  // cyan
        color4(0.0, 0.0, 0.0, 1.0),  // black
};

// Model-view and projection matrices uniform location
GLuint Projection;
GLuint Model;
GLuint View;
GLuint Color;

World *world;

//----------------------------------------------------------------------------

// OpenGL initialization
void init() {
    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");

    // Retrieve transformation uniform variable locations
    Projection = glGetUniformLocation(program, "Projection");
    Model = glGetUniformLocation(program, "Model");
    View = glGetUniformLocation(program, "View");
    Color = glGetUniformLocation(program, "Color");

    // Set current program object
    glUseProgram(program);

    world = new World(program);

    // Enable hiddden surface removal
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set state variable "clear color" to clear buffer with.
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

//----------------------------------------------------------------------------

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world->drawObjects(Model, View, Projection, Color);

    glutSwapBuffers();
}

//---------------------------------------------------------------------
//
// reshape
//

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	mat4 projection = Perspective(45.0, (GLfloat) w / (GLfloat) h, 0.5, 100.0);

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}


//----------------------------------------------------------------------------

void idle(void) {
    glutPostRedisplay();
}

void animationTimer(int arg) {
    glutTimerFunc(40, animationTimer, arg - 1);
}

void globalMoveForwardBackward(float amt) {
    // Do not move in Y-axis
    float temp = eye.y;
	eye += amt * -viewDirection;
	eye.y = temp;
    mat4 view = LookAt(eye, eye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);

}

void globalMoveLeftRight(float amt) {
	eye += amt * cross(viewDirection, up);
	mat4 view = LookAt(eye, eye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);

}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': case'S': //based on camera mode, update view matrix/move ball
            globalMoveForwardBackward(0.1);
            break;
        case 'w': case 'W'://based on camera mode, update view matrix/move ball
            globalMoveForwardBackward(-0.1);
            break;
        case 'a': case 'A'://based on camera mode, update view matrix/move ball
            globalMoveLeftRight(-0.1);
            break;
        case 'd': case 'D'://based on camera mode, update view matrix/move ball
            globalMoveLeftRight(0.1);
            break;
    }
}

void mouse(int x, int y) {
	vec2 currentMousePosition = vec2(x, y);
	vec2 mouseDisplacement = currentMousePosition - previousMousePosition;
	if (length(mouseDisplacement) > 50.0f) {
		previousMousePosition = currentMousePosition;
		return;
	}

	glm::vec3 vector = glm::vec3(viewDirection.x, viewDirection.y, viewDirection.z);
	vector = glm::mat3(glm::rotate(-mouseDisplacement.x * (GLfloat)0.006, glm::vec3(up.x, up.y, up.z))) * vector;

	glm::vec3 rotateAround = glm::cross(vector, glm::vec3(up.x, up.y, up.z));
	vector = glm::mat3(glm::rotate(-mouseDisplacement.y * (GLfloat)0.006, rotateAround)) * vector;
	viewDirection = vec4(vector.x, vector.y, vector.z, 0.0f);
	previousMousePosition = currentMousePosition;
	
	mat4 view = LookAt(eye, eye + viewDirection, up);
	glUniformMatrix4fv(View, 1, GL_TRUE, view);
}

//----------------------------------------------------------------------------

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Maze");

    glewExperimental = GL_TRUE;
    glewInit();

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);

    glutMainLoop();
    return 0;
}