#ifndef __SCREEN__H
#define __SCREEN__H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

#include "HelperClass.h"

using namespace std;

class Screen
{
public:
	bool ShouldClose();
	Screen(int width, int height, string title , bool resizeable = false);
	void CreateWindow();

	string GetTitle();
	GLuint GetHeight();
	GLuint GetWidth();
	void Clear();

	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetMouseInTheWindow();
	vec2 GetMousePos();
	bool GetMouseKeyDown(int key);
	bool GetMouseKey(int key);
	vec2 GetScrollDelta();

private:
	GLFWwindow* m_window;
	GLuint m_width, m_height;

	string m_title;
	bool m_resizeable = false;
	static vector<Screen*> allScreens;

	friend int findScreen(GLFWwindow* window);
	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void cursor_enter_callback(GLFWwindow* window, int entered);
	friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	bool m_mouseInScreen = false;
	GLbyte m_mouseKeyState[3] = { 0 };
	GLbyte m_keyState[1024] = { 0 };
	vec2 m_scrollDelta;
};
#endif

