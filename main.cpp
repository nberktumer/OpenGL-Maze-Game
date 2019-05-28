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
GLuint program;

World *world;

int gameState = 0; // 0 - Start, 1 - Rotate the camera 180 degrees in X-axis, 2 - Play, 3 - Bring the tropy closer, 4 - Rotate the trophy

//----------------------------------------------------------------------------

// OpenGL initialization
void init() {
    // Load shaders and use the resulting shader program
    program = InitShader("vshader.glsl", "fshader.glsl");

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
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
            if(gameState != 2)
                return;
            world->moveBackward(View, 0.1);
            break;
        case 'w': case 'W':
            if(gameState != 2)
                return;
            world->moveForward(View, 0.1);
            break;
        case 'a': case 'A':
            if(gameState != 2)
                return;
            world->moveLeft(View, 0.1);
            break;
        case 'd': case 'D':
            if(gameState != 2)
                return;
            world->moveRight(View, 0.1);
            break;
        case '1':
            world = new World(program);
            gameState = 0;
            break;
    }
}

void mouse(int x, int y) {
    if(gameState != 2)
        return;

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

void timer(int p) {
	if(gameState == 0) {
        if(world->closeDoors()) { // Close the enterence
            gameState = 1;
        }
        glutTimerFunc(33, timer, 0);
    } else if(gameState == 1) { // Rotate the camera by 180 degree in X-axis
        if(p < 100) {
            world->rotateCamera(View, vec2(5, 0));
            glutTimerFunc(33, timer, p + 1);
        } else {
            gameState = 2;
            glutTimerFunc(33, timer, 0);
        }
    } else if(gameState == 2) { // Check if the player has reached the exit
        if(world->hasReachedTheEnd()) {
            gameState = 3;
        }
        glutTimerFunc(33, timer, 0);
    } else if(gameState == 3) { // Bring the trophy
        if(world->animateTheTropy()) {
            gameState = 4;
        }
        glutTimerFunc(33, timer, 0);
    } else { // Rotate the trophy
        world->rotateTheTropy();
    }

	glutPostRedisplay();

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
	glutTimerFunc(33, timer, 0);

    glutMainLoop();
    return 0;
}