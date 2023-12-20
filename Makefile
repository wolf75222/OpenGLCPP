# Detecting the operating system
UNAME_S := $(shell uname -s)

# default paths for macOS
BASE_PATH := /opt/homebrew/opt
LIB_FLAG := -framework OpenGL

# Adjust for Arch Linux
ifeq ($(UNAME_S),Linux)
    BASE_PATH := /usr
    LIB_FLAG := -lGL
endif

# Library paths
GLEW_PATH := $(BASE_PATH)/glew
GLFW_PATH := $(BASE_PATH)/glfw
GLM_PATH := $(BASE_PATH)/glm

# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -std=c++11

# Header locations
INCLUDES := -I$(GLEW_PATH)/include -I$(GLFW_PATH)/include -I$(GLM_PATH)/include

# Library locations
LIBS := -L$(GLEW_PATH)/lib -L$(GLFW_PATH)/lib

# Library links
LFLAGS := -lglfw -lGLEW $(LIB_FLAG)

# Source files
SRCS := src/main.cpp src/Camera.cpp src/Renderer.cpp src/Shader.cpp

# Object files, placed in the build folder
OBJS := $(SRCS:src/%.cpp=build/%.o)

# Program name
TARGET := build/myOpenGLApp

# Main rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS) $(LFLAGS)

# Create build folder if necessary
build/%.o: src/%.cpp
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	$(RM) -r build

