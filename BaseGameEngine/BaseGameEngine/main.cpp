#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "BasicMat.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

void main()
{
	Screen screen(WIDTH , HEIGHT , "OpenGL Test");
	screen.CreateWindow();
	Scene scene(&screen);
	Camera camera;
	Object cameraObj(&camera);
	cameraObj.GetTransform().Position = vec3(0, -5, -20);
	
	scene.LoadFile<BasicMat>("./models/nanosuit2/nanosuit2.obj");
	scene.AddCamera(&camera);
	scene.UpdateLoop();
	
	glfwTerminate();
}