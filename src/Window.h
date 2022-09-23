#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>

GLFWwindow *create_window();

typedef enum {
	ONE = 0,
	TWO,
	THREE,
	FOUR,
} State;

State current_state();

#endif //_WINDOW_H_
