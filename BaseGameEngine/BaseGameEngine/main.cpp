#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
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
	cameraObj.GetTransform().Position = vec3(0, 0, -20);
	
	/*BasicTexMat mat;
	Texture* texture = Texture::GetTexture("./models/nanosuit2/leg_showroom_spec.png");
	mat.SetTexture(texture);
	Mesh mesh(PLANE);
	Object object(&mat, &mesh);
	scene.AddObject(object);*/
	
	scene.LoadFile<BasicTexMat>("./models/nanosuit2/tex/nanosuit2.obj");
	scene.UpdateLoop();
	
	glfwTerminate();
}