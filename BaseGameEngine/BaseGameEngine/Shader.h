#ifndef __SHADER_H
#define __SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

//my Headers

#include "HelperClass.h"

using namespace std;

class Shader
{
public:

	static Shader* GetShader(const string vertexPath , const string fragmentPath);
	GLuint inline GetShaderId();
	void Use();
	static void UnUse();

private:
	static vector<Shader*> m_allShader;
	
	GLuint m_shaderId;

	string m_vertexPath;
	string m_fragmentPath;
	

	Shader(const string vertexPath, const string fragmentPath);
	void CheckCompileState(GLuint shaderToCheck , int whatToCheck , string toPrintInError);
};

#endif