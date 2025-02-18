#pragma once
#include "common.h"
#include "vectorMath.h"

class InputManager {
public:
	inline static map<int, bool> keyState;

	static void init(GLFWwindow* window);

	static void keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods);
};