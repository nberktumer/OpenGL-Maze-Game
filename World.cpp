#include "World.h"

World::World(GLuint program) {
    this->program = program;

    for(int i = 0; i < worldHeight; i++) {
        for(int j = 0; j < worldWidth; j++) {
            int value = map[i][j];

            switch (value) {
                case 0: // Path
                    addObject(new Path(i * cellSize, -Wall::HEIGHT / 2 + Path::HEIGHT / 2, j * cellSize));
                    break;
                case 1: // Wall
                    addObject(new Wall(i * cellSize, 0, j * cellSize));
                    break;
                case 2: { // Enterence
                    vec3 cameraDirection;
                    if(i == 0) {
                        cameraDirection = vec3(1.0, 0.0, 0.0);
                    } else if(i == worldHeight - 1) {
                        cameraDirection = vec3(-1.0, 0.0, 0.0);
                    } else if(j == 0) {
                        cameraDirection = vec3(0.0, 0.0, 1.0);
                    } else {
                        cameraDirection = vec3(0.0, 0.0, -1.0);
                    }
                    this->camera = new Camera(
                        vec3(i * cellSize, 0, j * cellSize),
                        cameraDirection,
                        vec3(0, 1, 0)
                    );
                    addObject(new Path(i * cellSize, -Wall::HEIGHT / 2 + Path::HEIGHT / 2, j * cellSize));
                    break;
                }
                case 3: // Exit
                    addObject(new Path(i * cellSize, -Wall::HEIGHT / 2 + Path::HEIGHT / 2, j * cellSize));
                    break;
                default:
                    break;
            }
        }
    }
}


World::~World() {
}

void World::addObject(BaseObject *object) {
	//add the object to vector for drawing later
	//set the objects VAO and buffer its VBO with vertices and normals.

	objects.push_back(object);
	object->setVectorIndex(objects.size() - 1);

	vector<vec4> vertices = object->getVertices();
	vector<vec3> normals = object->getNormals();

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	GLuint vNormal = glGetAttribLocation(program, "vNormal");

	glGenVertexArrays(1, &object->vao);

	// Bind to Cube buffer
	glBindVertexArray(object->vao);

	// Cube buffer
	glGenBuffers(1, &object->buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4) + normals.size() * sizeof(vec3), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vec4), &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4), normals.size() * sizeof(vec3), &normals[0]);

	// Cube vertex arrays
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(vec4)));
}
 
void World::drawObjects(GLuint Model, GLuint Color) {
	for (int i = 0; i < objects.size(); i++) {
		BaseObject *obj = objects.at(i);
		obj->draw(Model, Color);
	}
}

void World::moveForward(GLuint View, float amount) {
    camera->moveForward(View, -amount, getBoundries());
}

void World::moveBackward(GLuint View, float amount) {
    camera->moveForward(View, amount, getBoundries());
}

void World::moveRight(GLuint View, float amount) {
    camera->moveRight(View, amount, getBoundries());
}

void World::moveLeft(GLuint View, float amount) {
    camera->moveRight(View, -amount, getBoundries());
}

void World::rotateCamera(GLuint View, vec2 displacement) {
    camera->rotate(View, displacement);
}

Boundry_t World::getBoundries() {
    vec3 currentPosition = camera->getPosition();
    int i = (currentPosition.x + cellSize / 2) / cellSize;
    int j = (currentPosition.z + cellSize / 2) / cellSize;

    Boundry_t boundries;
    boundries.cellSize = cellSize;
    boundries.center = vec3(i * cellSize, 0.0, j * cellSize);
    
    if(i == 0) {
        boundries.bottom = 1;
        boundries.top = map[i + 1][j];
    } else if(i == worldHeight - 1) {
        boundries.bottom = map[i - 1][j];
        boundries.top = 1;
    } else {
        boundries.bottom = map[i - 1][j];
        boundries.top = map[i + 1][j];
    }

    if(j == 0) {
        boundries.left = 1;
        boundries.right = map[i][j + 1];
    } else if(j == worldWidth - 1) {
        boundries.left = map[i][j - 1];
        boundries.right = 1;
    } else {
        boundries.left = map[i][j - 1];
        boundries.right = map[i][j + 1];
    }
    
    return boundries;
}