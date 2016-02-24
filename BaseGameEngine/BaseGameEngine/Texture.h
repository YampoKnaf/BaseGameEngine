#ifndef __TEXTURE__H
#define __TEXTURE__H

#include <GL\glew.h>
#include <unordered_map>
#include <SOIL\SOIL.h>

using namespace std;

class Texture
{
public:
	Texture* GetTexture(string fileName);
	void Bind(int Index, string name , GLuint shaderID);

private:
	GLuint textureID;
	Texture(string fileName);
	~Texture();

	static unordered_map<string, Texture*> allTextures;
};
#endif

