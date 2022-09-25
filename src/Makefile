CC=clang++
# NOTE(__LUNA__): To make truly linux compatible detect os and remove frameworks.
CFLAGS=-std=c++17 -Wall -Wextra -pedantic -framework Cocoa -framework OpenGL -framework IOKit `pkg-config glfw3 --cflags`
LIBS=`pkg-config glfw3 --static --libs`
SRC=main.cpp glad.cpp Sandbox.cpp Window.cpp Texture.cpp Shader.cpp Shape.cpp Math.cpp

OpenGLPractice: $(SRC)
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o OpenGLPractice
