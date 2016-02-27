#include "Screen.h"

#define FIND_SCREEN int index = findScreen(window);if (index == -1)return;Screen* screen = Screen::allScreens[index];

vector<Screen*> Screen::allScreens;

int findScreen(GLFWwindow* window)
{
	int index = 0;
	for (Screen* screen : Screen::allScreens)
	{
		if (screen->m_window == window)
			return index;
		index++;
	}
	return -1;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	FIND_SCREEN;
	screen->m_scrollDelta = vec2(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	FIND_SCREEN;
	screen->m_mouseKeyState[button] = action;
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	FIND_SCREEN;
	screen->m_mouseInScreen = entered != false;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	FIND_SCREEN;
	screen->m_keyState[key] = action;
}

Screen::Screen(int width, int height, string title , bool resizeable):m_width(width) , m_height(height) , m_title(title) , m_resizeable(resizeable)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizeable ? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

void Screen::CreateWindow()
{
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		throw "Failed to create GLFW window";
	}
	glfwMakeContextCurrent(m_window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		throw "Failed to initialize GLEW";
	}

	//Define the the color of the default backgraud
	glClearColor(0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorEnterCallback(m_window, cursor_enter_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
	//Add to static vector of screen pointers
	allScreens.push_back(this);
}

string Screen::GetTitle()
{
	return string();
}

GLuint Screen::GetHeight()
{
	return m_height;
}

GLuint Screen::GetWidth()
{
	return m_width;
}

void Screen::Clear()
{
	glfwSwapBuffers(m_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Screen::GetKey(int key)
{
	if (key < 0 || key >= 1024)
		return false;
	return m_keyState[key] != GLFW_RELEASE;
}

bool Screen::GetKeyDown(int key)
{
	if (key < 0 || key >= 1024)
		return false;
	return m_keyState[key] == GLFW_PRESS;
}

vec2 Screen::GetMousePos()
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return vec2(x, y);
}

bool Screen::GetMouseKeyDown(int key)
{
	if (key < 0 || key >= 3)
		return false;
	return m_mouseKeyState[key] == GLFW_PRESS;
}

bool Screen::GetMouseKey(int key)
{
	if (key < 0 || key >= 3)
		return false;
	return m_mouseKeyState[key] != GLFW_RELEASE;
}

vec2 Screen::GetScrollDelta()
{
	return m_scrollDelta;
}

bool Screen::GetMouseInTheWindow()
{
	return m_mouseInScreen;
}
