#include "Angel.h"
#include "World.h"
#include <stdlib.h>
#include <vector>

using namespace std;

void init(void);

void display(void);

void reshape(int w, int h);

void idle(void);

void keyboard(unsigned char key, int x, int y);

int main(int argc, char **argv);

vec2 previousMousePosition = vec2(0, 0);

// Model-view and projection matrices uniform location
GLuint Projection;
GLuint Model;
GLuint View;

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

    world->drawObjects(Model);

    glutSwapBuffers();
}

//---------------------------------------------------------------------
//
// reshape
//

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	mat4 projection = Perspective(45.0, (GLfloat) w / (GLfloat) h, 0.001, 100.0);

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}


//----------------------------------------------------------------------------

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': case'S':
            world->moveBackward(View, 0.1);
            break;
        case 'w': case 'W':
            world->moveForward(View, 0.1);
            break;
        case 'a': case 'A':
            world->moveLeft(View, 0.1);
            break;
        case 'd': case 'D':
            world->moveRight(View, 0.1);
            break;
    }
}

void mouse(int x, int y) {
	vec2 currentMousePosition = vec2(x, y);
	vec2 displacement = currentMousePosition - previousMousePosition;
	if (length(displacement) > 50.0f) {
		previousMousePosition = currentMousePosition;
		return;
	}
    previousMousePosition = currentMousePosition;

    world->rotateCamera(View, displacement);
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