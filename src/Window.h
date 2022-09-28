#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef enum {
	ONE = 0,
	TWO,
	THREE,
	FOUR,
} State;

typedef enum {
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT
} Dir;

State current_state();
float current_mix();

typedef struct {
	float offsetX, offsetY;
} MousePos;

MousePos current_mouse_pos();

// NOTE(__LUNA__): Absolutely abominable
GLFWwindow *create_window();
bool move_up(GLFWwindow *window);
bool move_down(GLFWwindow *window);
bool move_left(GLFWwindow *window);
bool move_right(GLFWwindow *window);

#endif //_WINDOW_H_
