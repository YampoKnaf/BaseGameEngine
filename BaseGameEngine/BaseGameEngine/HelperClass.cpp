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
