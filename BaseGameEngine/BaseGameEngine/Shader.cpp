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

inline GLuint Shader::GetShaderId()
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

Shader::Shader(const string vertexPath, const string fragmentPath)
{
	string vertexCode	= HelperClass::ReadFromFile(vertexPath.c_str());
	string fragmentCode = HelperClass::ReadFromFile(fragmentPath.c_str());
	const char* tempChar;
	GLuint m_vertexId;
	GLuint m_fragmentId;

	m_vertexId = glCreateShader(GL_VERTEX_SHADER);
	tempChar = vertexCode.c_str();
	glShaderSource(m_vertexId, 1, &tempChar, NULL);
	glCompileShader(m_vertexId);
	CheckCompileState(m_vertexId , GL_COMPILE_STATUS, "VERTEX");

	m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	tempChar = vertexCode.c_str();
	glShaderSource(m_fragmentId, 1, &tempChar, NULL);
	glCompileShader(m_fragmentId);
	CheckCompileState(m_fragmentId, GL_COMPILE_STATUS, "FRAGMENT");

	this->m_shaderId = glCreateProgram();
	glAttachShader(this->m_shaderId, m_vertexId);
	glAttachShader(this->m_shaderId, m_fragmentId);
	glLinkProgram(this->m_shaderId);

	CheckCompileState(m_shaderId, GL_LINK_STATUS, "SHADER_PROGRAM");

	glDeleteShader(m_vertexId);
	glDeleteShader(m_fragmentId);
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
