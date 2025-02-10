#include "EventManager.h"

void EventManager::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keybEventManager);
}

void EventManager::keybEventManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action) 
	{
	case GLFW_PRESS:
		keyState[key] = true;
		break;

	case GLFW_REPEAT:
		break;

	case GLFW_RELEASE:
		keyState[key] = false;
		break;
	}
}
