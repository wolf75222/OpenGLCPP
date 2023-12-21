#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Renderer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <unistd.h>




// Paramètres de la fenêtre
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Initialisation de la caméra avec un angle de vue de 45 degrés
Camera camera(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f);

float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        camera.Move(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Move(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Move(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Move(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ToggleAutoRotate();
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        camera.Move(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        camera.Move(DOWN, deltaTime);
    }




    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      // augemente la vitesse de la camere 
      camera.IncreaseSpeed();
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int main() {

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      std::cout << "Current working dir: " << cwd << std::endl;
    } else {
      perror("getcwd() error");
    }
    glfwInit();
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Pour macOS

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 2.1 C++", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Capture de la souris
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Configuration initiale de la caméra (si nécessaire)
    
    // Création des shaders
   
    Shader gridShader; // Déclaration en dehors du bloc try

    try {
        gridShader = Shader("/Users/romaindespoulain/Documents/OpenGLCPP/src/Shader/grid.vert", 
                            "/Users/romaindespoulain/Documents/OpenGLCPP/src/Shader/grid.frag");
    } catch (const std::exception& e) {
        std::cerr << "Shader compilation/loading error: " << e.what() << std::endl;
        return -1; // Quittez le programme en cas d'erreur
    }

    printf("Shader loaded\n");

    gridShader.ReloadShader("/Users/romaindespoulain/Documents/OpenGLCPP/src/Shader/grid.vert", 
                            "/Users/romaindespoulain/Documents/OpenGLCPP/src/Shader/grid.frag");

    printf("Shader reloaded\n");

    Renderer::InitGrid(15.0f, 15);

    printf("Grid loaded\n");

    // Avant la boucle de rendu
    glm::mat4 model = glm::mat4(1.0f); // Crée une matrice de modèle identité

    printf("Starting loop\n");

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        // Mise à jour du timing
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Traitement des entrées
        processInput(window);

        //rotate 
        camera.Rotate(deltaTime * 10.0f);

        // Mise à jour de la matrice de vue et de projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // Rendu de la scène
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Utilisation de la caméra
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(&projection[0][0]);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

        gridShader.setMat4("projection", projection);
        gridShader.setMat4("view", view);
        gridShader.setMat4("model", model);


        Renderer::DrawGrid(gridShader);



        // Utilisez les shaders ici
        // Dessinez les axes et le quadrillage
        Renderer::DrawAxis(5.0f);
        //Renderer::DrawGrid(10.0f, 10);
        
        Renderer::DrawSphere(1.0f, 0.0f, 0.0f, 0.0f, 20, 1.0f, 1.0f, 1.0f);

        //Renderer::DrawCube(1.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

