#pragma once
#include "common.h"
#include "vectorMath.h"

typedef struct {
	double x, y;
	map<int, bool> buttonState;
} mouseState_t;

class EventManager {
public:
	inline static map<int, bool> keyState;
	inline static mouseState_t mouseState;

	static void init(GLFWwindow* window);

	static void keybEventManager(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mousePosManager(GLFWwindow* window, double xpos, double ypos);

	static void mouseButtonManager(GLFWwindow* window, int button, int action, int mods);
};