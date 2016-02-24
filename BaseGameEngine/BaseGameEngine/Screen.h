#ifndef __SCREEN__H
#define __SCREEN__H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

using namespace std;

class Screen
{
public:
	Screen(int width, int height, string title , bool resizeable = false);
	void CreateWindow();

	string GetTitle();
	GLuint GetHeight();
	GLuint GetWidth();
	void Clear();

private:
	GLFWwindow* m_window;
	GLuint m_width, m_height;

	string m_title;
	bool m_resizeable = false;
	static vector<Screen*> allScreens;
	
};
#endif

