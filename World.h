#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "Wall.h"
#include "Path.h"
#include "Door.h"
#include "Tropy.h"
#include "Camera.h"
#include "Boundry.h"
#include <vector>

using namespace std;

class World {
    public:
        static constexpr float cellSize = 3.0;
        inline static vec4 light_ambient = vec4(1.0, 1.0, 1.0, 1.0 );
        inline static vec4 light_diffuse = vec4(1.0, 1.0, 1.0, 1.0 );
        inline static vec4 light_specular = vec4(1.0, 1.0, 1.0, 1.0 );
    
        World(GLuint program);
        ~World();
        void addObject(BaseObject* object);
        void addObjectWithColor(BaseObject* object);
        void drawObjects(GLuint Model);
        void moveForward(GLuint View, float amount);
        void moveBackward(GLuint View, float amount);
        void moveRight(GLuint View, float amount);
        void moveLeft(GLuint View, float amount);
        void rotateCamera(GLuint View, vec2 displacement);
        bool closeDoors();
        bool hasReachedTheEnd();
        bool animateTheTropy();
        void rotateTheTropy();
    private:
        GLuint program;
        GLuint textureList[2];
        Door *door1, *door2;
        Tropy *tropy;
        vector<BaseObject*> objects;
        vec2 enterence;
        static constexpr const int worldWidth = 21;
        static constexpr const int worldHeight = 21;

        /**
         * Map Info
         * 0: Path
         * 1: Wall
         * 2: Enterence
         * 3: Exit
         */
        const int map[worldWidth][worldHeight] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3},
            {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
            {2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };
        Camera *camera;
        Boundry_t getBoundries();
        void loadTextures();
        GLubyte* readTexture(string path, int *width, int *height);
        const vec4 light_position = vec4(1.0, -1.0, 1.0, 1.0);
        const vec3 light_location = vec3(-3.0, 10.0, -3.0);
};

#endif