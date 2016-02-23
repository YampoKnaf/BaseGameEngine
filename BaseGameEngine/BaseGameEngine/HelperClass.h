#ifndef __HELPER_CLASS_H
#define __HELPER_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>


class HelperClass
{
public:
	static std::string ReadFromFile(const GLchar* path);
};

#endif