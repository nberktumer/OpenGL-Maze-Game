#pragma once
#ifndef TROPY_H
#define TROPY_H
#include "BaseObject.h"

class Tropy : public BaseObject {
    public:
        Tropy(GLuint program, float x, float y, float z);
        ~Tropy();
        void draw(GLuint Model);
};

#endif
