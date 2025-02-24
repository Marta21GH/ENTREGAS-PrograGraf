#include "EventManager.h"

void EventManager::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keybEventManager);
	glfwSetMouseButtonCallback(window, mouseButtonManager);
	glfwSetCursorPosCallback(window, mousePosManager);
}

void EventManager::keybEventManager(GLFWwindow* window, int key, int scancode, int action, int mods)
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

void EventManager::mousePosManager(GLFWwindow* window, double xpos, double ypos)
{
	mouseState.x = xpos;
	mouseState.y = ypos;
}

void EventManager::mouseButtonManager(GLFWwindow* window, int button, int action, int mods)
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
