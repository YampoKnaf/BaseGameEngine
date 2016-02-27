#include "HelperClass.h"

string ReadFromFile(const GLchar * path)
{
	std::string codeToReturn;
	std::ifstream fileToOpen;
	// ensures ifstream objects can throw exceptions:
	fileToOpen.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		fileToOpen.open(path);
		std::stringstream fileStream;
		// Read file's buffer contents into streams
		fileStream << fileToOpen.rdbuf();
		// close file handlers
		fileToOpen.close();
		// Convert stream into string
		codeToReturn = fileStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return nullptr;
	}
	return codeToReturn;
}

mat4 aiMatrix4x4ToMat4(aiMatrix4x4 aiMatrix4x4)
{
	mat4 matrix;
	matrix[0].x = aiMatrix4x4.a1;
	matrix[0].y = aiMatrix4x4.a2;
	matrix[0].z = aiMatrix4x4.a3;
	matrix[0].w = aiMatrix4x4.a4;

	matrix[1].x = aiMatrix4x4.b1;
	matrix[1].y = aiMatrix4x4.b2;
	matrix[1].z = aiMatrix4x4.b3;
	matrix[1].w = aiMatrix4x4.b4;

	matrix[2].x = aiMatrix4x4.c1;
	matrix[2].y = aiMatrix4x4.c2;
	matrix[2].z = aiMatrix4x4.c3;
	matrix[2].w = aiMatrix4x4.c4;

	matrix[3].x = aiMatrix4x4.d1;
	matrix[3].y = aiMatrix4x4.d2;
	matrix[3].z = aiMatrix4x4.d3;
	matrix[3].w = aiMatrix4x4.d4;

	return matrix;
}
