#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <assimp\Importer.hpp>
#include <SOIL\SOIL.h>

void main()
{
	glfwInit();
	glewInit();
	Assimp::Importer imp;
	printf("hii world\n");
	system("pause");
}