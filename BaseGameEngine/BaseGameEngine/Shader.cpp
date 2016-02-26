#include "Shader.h"

vector<Shader*> Shader::m_allShader;

Shader* Shader::GetShader(const string vertexPath, const string fragmentPath)
{
	for (Shader* shad : m_allShader)
	{
		if (vertexPath.compare(shad->m_vertexPath) == 0 && fragmentPath.compare(shad->m_fragmentPath) == 0)
			return shad;
	}
	return new Shader(vertexPath, fragmentPath);
}

GLuint Shader::GetShaderId()
{
	return m_shaderId;
}

void Shader::Use()
{
	glUseProgram(this->m_shaderId);
}

void Shader::UnUse()
{
	glUseProgram(0);
}

Shader::Shader(const string vertexPath, const string fragmentPath):m_vertexPath(vertexPath) , m_fragmentPath(fragmentPath)
{
	string vertexCode	= ReadFromFile(vertexPath.c_str());
	string fragmentCode = ReadFromFile(fragmentPath.c_str());
	const char* tempChar;
	GLuint vertexId;
	GLuint fragmentId;

	vertexId = glCreateShader(GL_VERTEX_SHADER);
	tempChar = vertexCode.c_str();
	glShaderSource(vertexId, 1, &tempChar, NULL);
	glCompileShader(vertexId);
	CheckCompileState(vertexId , GL_COMPILE_STATUS, "VERTEX");

	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	tempChar = fragmentCode.c_str();
	glShaderSource(fragmentId, 1, &tempChar, NULL);
	glCompileShader(fragmentId);
	CheckCompileState(fragmentId, GL_COMPILE_STATUS, "FRAGMENT");

	this->m_shaderId = glCreateProgram();
	glAttachShader(this->m_shaderId, vertexId);
	glAttachShader(this->m_shaderId, fragmentId);
	glLinkProgram(this->m_shaderId);

	CheckCompileState(m_shaderId, GL_LINK_STATUS, "SHADER_PROGRAM");

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::CheckCompileState(GLuint shaderToCheck, int whatToCheck, string toPrintInError)
{
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shaderToCheck, whatToCheck, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderToCheck, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << toPrintInError << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
