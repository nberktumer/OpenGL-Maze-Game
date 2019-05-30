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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set the world color to black.
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

//----------------------------------------------------------------------------

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render all the objects in the world
    world->drawObjects(Model);

    glutSwapBuffers();
}

//---------------------------------------------------------------------

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

    // Use perspective projection
	mat4 projection = Perspective(45.0, (GLfloat) w / (GLfloat) h, 0.001, 100.0);

	glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}


//----------------------------------------------------------------------------

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': case 'S': // Move backwards
            if(gameState != 2)
                return;
            world->moveBackward(View, 0.1);
            break;
        case 'w': case 'W': // Move forward
            if(gameState != 2)
                return;
            world->moveForward(View, 0.1);
            break;
        case 'a': case 'A': // Move left
            if(gameState != 2)
                return;
            world->moveLeft(View, 0.1);
            break;
        case 'd': case 'D': // Move right
            if(gameState != 2)
                return;
            world->moveRight(View, 0.1);
            break;
        case '1': // Reload the world
            world = new World(program);
            gameState = 0;
            break;
        case 'h': case 'H':
            cout << "HELP:" << endl << endl;
            cout << "W: Move Forward" << endl;
            cout << "A: Move Left" << endl;
            cout << "S: Move Backwards" << endl;
            cout << "D: Move Right" << endl << endl;
            cout << "Mouse: Rotate mouse to look around" << endl << endl;
            cout << "1: Restart the game" << endl;
            cout << "H: Help" << endl; 
    }
}

/**
 * Looking around with mouse function is taken from Jamie King's OpenGL tutorial
 * https://www.youtube.com/watch?v=7oNLw9Bct1k
 */
void mouse(int x, int y) {
    // Do not rotate the camera if the game is not ready to play
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
    if(gameState == 0) { // Animate the door
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