#include "InputManager.h"

void InputManager::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyboardManager);
	glfwSetMouseButtonCallback(window, mouseButtonEvent);
	glfwSetCursorPosCallback(window, mousePosEvent);
}

void InputManager::keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action) {
	case GLFW_PRESS:
		keyState[key] = true;
		break;
	case GLFW_REPEAT:
		break;
	case GLFW_RELEASE:
		keyState[key] = false;
		break;
	default:
		break;
	}
}

void InputManager::mousePosEvent(GLFWwindow* window, double xpos, double ypos)
{
	mouseState.x = xpos;
	mouseState.y = ypos;
}

void InputManager::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	switch (action) {
	case GLFW_PRESS:
		mouseState.buttonState[button] = true;
		break;
	case GLFW_REPEAT:
		break;
	case GLFW_RELEASE:
		mouseState.buttonState[button] = false;
		break;
	default:
		break;
	}
}
