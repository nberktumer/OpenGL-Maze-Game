#include "World.h"

World::World(GLuint program) {
    this->program = program;

    for(int i = 0; i < worldHeight; i++) {
        for(int j = 0; j < worldWidth; j++) {
            int value = map[i][j];

            switch (value) {
            case 0: // Path
                break;
            case 1: // Wall
                addObject(new Wall(i * cellSize, 0, j * cellSize));
                break;
            case 2: // Enterence
                break;
            case 3: // Exit
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

void World::removeObject(BaseObject *object, bool deletePointer) {
	//delete the object from the vector and free its memory.

	if (object->getVectorIndex() < 0) {
		cout << "Invalid attempt at deleting object with index " << object->getVectorIndex() << endl;
	}
	else {
		//Fix vector indices of next elements
		for (int i = object->getVectorIndex() + 1; i < objects.size(); i++) {
			BaseObject *obj = objects.at(i);
			obj->setVectorIndex(obj->getVectorIndex() - 1);
		}

		objects.erase(objects.begin() + object->getVectorIndex());

		//TODO
		//delete object  ? 

		if (deletePointer) {
			cout << "Deleting pointer." << endl;
			delete object;
			object = NULL;
		}
	}
}
 
void World::drawObjects(GLint modelLoc, GLint viewLoc, GLint projectionLoc, GLint colorLoc) {

	//Draw each object with different view/projection matrices depending on the type (UI or game object).
	for (int i = 0; i < objects.size(); i++) {
		BaseObject *obj = objects.at(i);
		obj->draw(modelLoc, colorLoc);
	}
}