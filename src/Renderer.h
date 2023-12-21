#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"


class Renderer {
public:
    static void DrawAxis(float size);
    static void InitGrid(float size, int numberOfLines);
    static void DrawGrid(Shader& shader);
    static void DrawSphere(float radius, float x, float y, float z, int subdivisions, float red, float green, float blue);
    static void DrawCube(float sideLength, float x, float y, float z, float red, float green, float blue);
};


#endif
