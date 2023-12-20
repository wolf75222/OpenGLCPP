#include "Renderer.h"
#include <GL/glew.h>
#include <vector>
#include "Shader.h"
#include <iostream>


unsigned int gridVAO, gridVBO;

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
    
    // Couleur 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void Renderer::InitGrid(float size, int numberOfLines) {
    std::vector<float> vertices;

    // Calcule la distance entre chaque ligne
    float step = size / numberOfLines;
    float halfSize = size / 2.0f;

    printf("Initializing Grid...\n");
    printf("Step: %f, HalfSize: %f\n", step, halfSize);

    for (int i = 0; i <= numberOfLines; ++i) {
        float coord = -halfSize + i * step;


        // Ligne horizontale
        vertices.push_back(-halfSize); // x1
        vertices.push_back(0.0f);      // y1
        vertices.push_back(coord);     // z1

        vertices.push_back(halfSize);  // x2
        vertices.push_back(0.0f);      // y2
        vertices.push_back(coord);     // z2


        // Ligne verticale
        vertices.push_back(coord);     // x1
        vertices.push_back(0.0f);      // y1
        vertices.push_back(-halfSize); // z1

        vertices.push_back(coord);     // x2
        vertices.push_back(0.0f);      // y2
        vertices.push_back(halfSize);  // z2

    }

    printf("Total vertices: %lu\n", vertices.size());

    // Version 
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    glGenBuffers(1, &gridVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    printf("Grid Initialized.\n");
}

void Renderer::DrawGrid(Shader& shader) {
    shader.use();

    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    
    // Configurez les attributs de sommet ici
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int nombreDePoints = 100;

    glDrawArrays(GL_LINES, 0, nombreDePoints);
    
    glDisableVertexAttribArray(0);
}

