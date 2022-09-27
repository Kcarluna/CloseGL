CC=clang++
# NOTE(__LUNA__): To make truly linux compatible detect os and remove frameworks.
UNAME_S:=$(shell uname -s)
CFLAGS=-std=c++17 -Wall -Wextra -pedantic `pkg-config glfw3 --cflags`
LIBS=`pkg-config glfw3 --static --libs`

ifeq ($(UNAME_S), Darwin)
	LIBS+=-framework Cocoa -framework OpenGL -framework IOKit
endif

SRC=main.cpp glad.cpp Sandbox.cpp Window.cpp Texture.cpp Shader.cpp Shape.cpp Math.cpp

CloseGL: $(SRC)
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o CloseGL
