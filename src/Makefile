CC=clang
CFLAGS=-std=c17 -Wall -Wextra -pedantic -framework Cocoa -framework OpenGL -framework IOKit `pkg-config glfw3 --cflags`
LIBS=`pkg-config glfw3 --static --libs`
SRC=main.c glad.c Sandbox.c Window.c Texture.c Shader.c Shape.c

OpenGLPractice: $(SRC)
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o OpenGLPractice
