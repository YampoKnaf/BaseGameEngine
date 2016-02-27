#include "Screen.h"

vector<Screen*> Screen::allScreens;

Screen::Screen(int width, int height, string title , bool resizeable):m_width(width) , m_height(height) , m_title(title) , m_resizeable(resizeable)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizeable ? GL_TRUE : GL_FALSE);
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
