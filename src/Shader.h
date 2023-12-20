#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    // ID du programme de shader
    unsigned int ID;
    
    // Constructeur par défaut
    Shader() {} 

    // Constructeur qui lit et construit le shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // Utiliser/activer le shader
    void use();

    // Fonctions utilitaires pour définir des uniformes dans les shaders
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

    void ReloadShader(const char* vertexPath, const char* fragmentPath);

};

#endif
