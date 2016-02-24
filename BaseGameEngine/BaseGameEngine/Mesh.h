#ifndef __MESH__H
#define __MESH__H

#include <GL\glew.h>
#include <assimp\scene.h>
#include <vector>

using namespace std;

class Mesh
{
public:
	Mesh(aiMesh* mesh);
	//Mesh(ShapeType shapeType);

	void Draw();
private:
	int m_numOfUVChannels;
	int m_numOfColorChannel;
	bool m_hasNormals;
	bool m_hasTangens;
	bool m_hasIndices;
	GLuint m_VAO;
	int m_size;

	void setMesh(vector<GLfloat>& vertices, vector<GLuint>* indices, int sizeOfVertex);
};

#endif