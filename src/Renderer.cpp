#include "Renderer.h"
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include <iostream>
#include <cmath>

void Renderer::DrawCube(float sideLength, float x, float y, float z, float red, float green, float blue) {
    glColor3f(red, green, blue); // Définir la couleur pour le cube

    float halfSide = sideLength / 2.0f;

    // Dessiner chaque face du cube
    glBegin(GL_QUADS);

    // Face avant
    glVertex3f(x - halfSide, y - halfSide, z + halfSide);
    glVertex3f(x + halfSide, y - halfSide, z + halfSide);
    glVertex3f(x + halfSide, y + halfSide, z + halfSide);
    glVertex3f(x - halfSide, y + halfSide, z + halfSide);

    // Face arrière
    glVertex3f(x - halfSide, y - halfSide, z - halfSide);
    glVertex3f(x + halfSide, y - halfSide, z - halfSide);
    glVertex3f(x + halfSide, y + halfSide, z - halfSide);
    glVertex3f(x - halfSide, y + halfSide, z - halfSide);

    // Face gauche
    glVertex3f(x - halfSide, y - halfSide, z - halfSide);
    glVertex3f(x - halfSide, y - halfSide, z + halfSide);
    glVertex3f(x - halfSide, y + halfSide, z + halfSide);
    glVertex3f(x - halfSide, y + halfSide, z - halfSide);

    // Face droite
    glVertex3f(x + halfSide, y - halfSide, z - halfSide);
    glVertex3f(x + halfSide, y - halfSide, z + halfSide);
    glVertex3f(x + halfSide, y + halfSide, z + halfSide);
    glVertex3f(x + halfSide, y + halfSide, z - halfSide);

    // Face du dessus
    glVertex3f(x - halfSide, y + halfSide, z - halfSide);
    glVertex3f(x - halfSide, y + halfSide, z + halfSide);
    glVertex3f(x + halfSide, y + halfSide, z + halfSide);
    glVertex3f(x + halfSide, y + halfSide, z - halfSide);

    // Face du dessous
    glVertex3f(x - halfSide, y - halfSide, z - halfSide);
    glVertex3f(x - halfSide, y - halfSide, z + halfSide);
    glVertex3f(x + halfSide, y - halfSide, z + halfSide);
    glVertex3f(x + halfSide, y - halfSide, z - halfSide);

    glEnd();
}


void Renderer::DrawSphere(float radius, float x, float y, float z, int subdivisions, float red, float green, float blue) {
    glColor3f(red, green, blue); // Définir la couleur pour la sphère

    for (int i = 0; i <= subdivisions; ++i) {
        float lat0 = M_PI * (-0.5 + (float)(i - 1) / subdivisions);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = M_PI * (-0.5 + (float)i / subdivisions);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= subdivisions; ++j) {
            float lng = 2 * M_PI * (float)(j - 1) / subdivisions;
            float lx = cos(lng);
            float ly = sin(lng);

            glVertex3f(lx * zr0 + x, ly * zr0 + y, z0 + z);
            glVertex3f(lx * zr1 + x, ly * zr1 + y, z1 + z);
        }
        glEnd();
    }
}





void Renderer::DrawAxis(float size) {
    glLineWidth(3.0f); // Augmenter l'épaisseur des lignes pour les axes

    glBegin(GL_LINES);
    // Axe X en rouge
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);

    // Axe Y en vert
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);

    // Axe Z en bleu
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    

    // Réinitialiser la couleur à blanc
    glColor3f(1.0, 1.0, 1.0);
    
    
    glEnd();

    glLineWidth(1.0f); // Remettre l'épaisseur des lignes à la valeur par défaut
}
/*
void Renderer::DrawGrid(float size, int numberOfLines) {
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f); // Couleur gris clair pour le quadrillage

    for (int i = -numberOfLines; i <= numberOfLines; ++i) {
        glVertex3f((float)i, 0, (float)-numberOfLines);
        glVertex3f((float)i, 0, (float)numberOfLines);

        glVertex3f((float)-numberOfLines, 0, (float)i);
        glVertex3f((float)numberOfLines, 0, (float)i);
    }

    glEnd();
}
*/



GLuint gridVBO; // Global ou membre de la classe Renderer


// Initialise le VBO pour un quadrilatère plein écran
void Renderer::InitGrid() {
    float quadVertices[] = {
        // Coordonnées pour un quadrilatère plein écran
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &gridVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Débinder le VBO
}

// Dessine le quadrilatère plein écran avec le shader de grille
void Renderer::DrawGrid(Shader& shader) {
    shader.use();
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);

    GLint posAttrib = glGetAttribLocation(shader.ID, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(posAttrib);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Débinder le VBO
}

