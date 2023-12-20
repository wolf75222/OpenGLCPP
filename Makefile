# Emplacements de base pour les bibliothèques
BASE_PATH = /opt/homebrew/opt
GLEW_PATH = $(BASE_PATH)/glew
GLFW_PATH = $(BASE_PATH)/glfw
GLM_PATH = $(BASE_PATH)/glm

# Compilateur
CC = g++

# Drapeaux du compilateur
CFLAGS = -Wall -std=c++11

# Emplacement des en-têtes
INCLUDES = -I$(GLEW_PATH)/include -I$(GLFW_PATH)/include -I$(GLM_PATH)/include

# Emplacement des bibliothèques
LIBS = -L$(GLEW_PATH)/lib -L$(GLFW_PATH)/lib

# Liens des bibliothèques
LFLAGS = -lglfw -lGLEW -framework OpenGL

# Fichiers source
SRCS = src/main.cpp src/Camera.cpp src/Renderer.cpp src/Shader.cpp

# Fichiers objets, placés dans le dossier build
OBJS = $(SRCS:src/%.cpp=build/%.o)

# Nom du programme
TARGET = build/myOpenGLApp

# Règle principale
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS) $(LFLAGS)

# Créer le dossier build si nécessaire
build/%.o: src/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Règle pour nettoyer
clean:
	$(RM) -r build

