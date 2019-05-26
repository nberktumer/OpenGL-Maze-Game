#pragma once
#ifndef BOUNDRY_H
#define BOUNDRY_H

#include "Angel.h"

struct Boundry {
    int top;
    int left;
    int right;
    int bottom;
    float cellSize;
    vec3 center;
} typedef Boundry_t;

#endif