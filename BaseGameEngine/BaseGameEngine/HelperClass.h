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
#include <unordered_map>

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

template<typename K , typename V>
bool FindInUnorderMapValueByKey(unordered_map<K, V>& map, K key, V** value)
{
	auto got = map.find(key);
	if (got == map.end())
		return false;
	else
	{
		*value = &got->second;
		return true;
	}
}

string ReadFromFile(const GLchar* path);
#endif