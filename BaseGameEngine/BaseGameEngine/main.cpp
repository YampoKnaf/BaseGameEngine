#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "RotateObject.h"

#include "BasicTexMat.h"
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
	scene.AddCamera(&camera);
	cameraObj.GetTransform().Position = vec3(0, -2, -5);
	
	Object* nanosuit = scene.LoadFile<BasicTexMat>("./models/nanosuit2/Nanosuit.obj");
	nanosuit->AddComponent(new RotateObject());
	scene.UpdateLoop();
	
	glfwTerminate();
}