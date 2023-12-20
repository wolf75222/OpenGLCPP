#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"


class Renderer {
public:
    static void DrawAxis(float size);
    static void InitGrid(float size, int numberOfLines);
    static void DrawGrid(Shader& shader);
};


#endif
