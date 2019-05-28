#include "World.h"

World::World(GLuint program) {
    this->program = program;

    loadTextures();

    // Add Directional Light Source
    GLuint lightLocation = glGetUniformLocation(program, "LightLocation");
	GLuint lightPosition = glGetUniformLocation(program, "LightPosition");
	GLuint ambientProduct = glGetUniformLocation(program, "AmbientProduct");
	GLuint diffuseProduct = glGetUniformLocation(program, "DiffuseProduct");
	GLuint specularProduct = glGetUniformLocation(program, "SpecularProduct");
    GLuint shininess = glGetUniformLocation(program, "Shininess");
    GLuint view = glGetUniformLocation(program, "View");

    glUniform4fv( ambientProduct, 1, light_ambient );
    glUniform4fv( diffuseProduct, 1, light_diffuse );
    glUniform4fv( specularProduct, 1, light_specular );
    glUniform1f( shininess, 256.0 );
    glUniform4fv( lightPosition, 1, light_position );
	glUniform3fv( lightLocation, 1, light_location );
    
    for(int i = 0; i < worldHeight; i++) {
        for(int j = 0; j < worldWidth; j++) {
            int value = map[i][j];

            switch (value) {
                case 0: // Path
                    addObject(new Path(program, textureList[1], i * cellSize, -Wall::HEIGHT / 2 + Path::HEIGHT / 2, j * cellSize));
                    break;
                case 1: // Wall
                    addObject(new Wall(program, textureList[0], i * cellSize, 0, j * cellSize));
                    break;
                case 2: { // Enterence
                    vec3 cameraDirection;
                    if(i == 0) {
                        cameraDirection = vec3(-1.0, 0.0, 0.0);
                    } else if(i == worldHeight - 1) {
                        cameraDirection = vec3(1.0, 0.0, 0.0);
                    } else if(j == 0) {
                        cameraDirection = vec3(0.0, 0.0, -1.0);
                    } else {
                        cameraDirection = vec3(0.0, 0.0, 1.0);
                    }
                    this->camera = new Camera(
                        view,
                        vec3(i * cellSize, 0, j * cellSize),
                        cameraDirection,
                        vec3(0, 1, 0)
                    );
                    enterence = vec2(i, j);
                    door1 = new Door(program, textureList[0], (i - 1) * cellSize, 0, (j - 1) * cellSize);
                    door2 = new Door(program, textureList[0], (i + 1) * cellSize, 0, (j - 1) * cellSize);
                    addObject(new Path(program, textureList[1], i * cellSize, -Wall::HEIGHT / 2 + Path::HEIGHT / 2, j * cellSize));
                    addObject(door1);
                    addObject(door2);
                    break;
                }
                case 3: // Exit
                    tropy = new Tropy(program, i * cellSize, -2, (j + 2) * cellSize);
                    addObjectWithColor(tropy);
                    addObject(new Path(program, textureList[1], i * cellSize, -Wall::HEIGHT / 2 + Path::HEIGHT / 2, j * cellSize));
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
    vector<vec2> textures = object->getTextures();

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	GLuint vNormal = glGetAttribLocation(program, "vNormal");
    GLuint vTexture = glGetAttribLocation(program, "vTexture");

	glGenVertexArrays(1, &object->vao);

	// Bind to Cube buffer
	glBindVertexArray(object->vao);

    glBindTexture(GL_TEXTURE_2D, object->texture);

	// Cube buffer
	glGenBuffers(1, &object->buffer);
	glBindBuffer(GL_ARRAY_BUFFER, object->buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4) + normals.size() * sizeof(vec3) + textures.size() * sizeof(vec2), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vec4), &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4), normals.size() * sizeof(vec3), &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4) + normals.size() * sizeof(vec3), textures.size() * sizeof(vec2), &textures[0]);

	// Cube vertex arrays
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(vec4)));

    glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size() * sizeof(vec4) + normals.size() * sizeof(vec3)));
}

void World::addObjectWithColor(BaseObject *object) {
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
 
void World::drawObjects(GLuint Model) {
	for (int i = 0; i < objects.size(); i++) {
		objects.at(i)->draw(Model);
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

void World::loadTextures() {
    glGenTextures(2, textureList);
    int n, m;

    GLubyte *stone = readTexture("stone.ppm", &n, &m);
	glBindTexture(GL_TEXTURE_2D, textureList[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_BYTE, stone);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    GLubyte *grass = readTexture("grass.ppm", &n, &m);
	glBindTexture(GL_TEXTURE_2D, textureList[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, n, m, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

GLubyte* World::readTexture(string path, int *width, int *height) {
    GLubyte *img;
    FILE *fd;
    int n, m;
    int k, nm;
    char c;
    int i;
    char b[100];
    float s;
    int red, green, blue;

    fd = fopen(path.c_str(), "r");
    fscanf(fd, "%[^\n] ", b);
    if (b[0] != 'P' || b[1] != '3') {
        exit(0);
    }
    fscanf(fd, "%c", &c);
    while (c == '#') {
        fscanf(fd, "%[^\n] ", b);
        fscanf(fd, "%c", &c);
    }
    ungetc(c, fd);
    fscanf(fd, "%d %d %d", &n, &m, &k);
    nm = n * m;
    img = (GLubyte *)malloc(3 * sizeof(GLuint) * nm);
    s = 255.0 / k;
    for (i = 0; i < nm; i++) {
        fscanf(fd, "%d %d %d", &red, &green, &blue);
		img[3 * nm - 3 * i - 3] = red * s;
        img[3 * nm - 3 * i - 2] = green * s;
        img[3 * nm - 3 * i - 1] = blue * s;
    }

    *width = n;
    *height = m;

    return img;
}

bool World::closeDoors() {
    door1->position.x += 0.01;
    door2->position.x -= 0.01;

    float xPos = enterence.x * cellSize - cellSize / 2;

    return door1->position.x > xPos;
}

bool World::hasReachedTheEnd() {
    vec3 currentPosition = camera->getPosition();
    int i = (currentPosition.x + cellSize / 2) / cellSize;
    int j = (currentPosition.z + cellSize / 2) / cellSize;

    return map[i][j] == 3;
}

bool World::animateTheTropy() {
    tropy->position.z -= 0.05;

    vec3 currentPosition = camera->getPosition();
    int i = (currentPosition.x + cellSize / 2) / cellSize;
    int j = (currentPosition.z + cellSize / 2) / cellSize;

    float zPos = (j + 1) * cellSize;
    
    return tropy->position.z < zPos;
}

void World::rotateTheTropy() {
    tropy->rotation.y += 1;
}