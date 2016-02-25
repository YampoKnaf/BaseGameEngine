#ifndef __HELPER_CLASS_H
#define __HELPER_CLASS_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

using namespace std;

template<typename T>
int FindElementInVector(vector<T>& vector, T& element)
{
	int index = 0;
	for (T var : vector)
	{
		if (var == element)
			return index;
		index++;
	}
	return -1;
}

template<typename T>
void RemoveElementInVector(vector<T>& vector, T& element)
{
	int index = FindElementInVector(vector, element);
	if (index == -1)
		return;
	vector.erase(vector.begin() + index);
}

string ReadFromFile(const GLchar* path);
#endif