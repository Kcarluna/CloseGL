#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>

typedef enum {
	ONE = 0,
	TWO,
	THREE,
	FOUR,
	END,
} State;

State current_state();
float current_mix();

GLFWwindow *create_window();

#endif //_WINDOW_H_
