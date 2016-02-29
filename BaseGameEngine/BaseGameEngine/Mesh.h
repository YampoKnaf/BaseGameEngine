#ifndef __MESH__H
#define __MESH__H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <assimp\scene.h>
#include <vector>
#include <unordered_map>

#include "HelperClass.h"

using namespace std;
using namespace glm;

enum ShapesTypes
{
	CUBE, SPHERE, PLANE, CYLINDER
};

class Mesh
{
public:
	
	static Mesh* GetMesh(aiMesh* mesh, string fileName , int index);
	Mesh(ShapesTypes shapeType, int resX = 10, int resY = 10);

	int NumOfUVChannels();
	int NumOfColorChannel();
	bool HasNormals();
	bool HasTangens();
	bool HasIndices();

	void Draw();
private:
	int m_numOfUVChannels;
	int m_numOfColorChannel;
	bool m_hasNormals;
	bool m_hasTangens;
	bool m_hasIndices;
	bool m_hasBones;
	GLuint m_VAO;//mesh id in the openGL
	int m_size;//number of vertices of if hasIndices number of indices
	Mesh(aiMesh* mesh);
	void SetBonesToMesh(aiMesh * mesh, int index);
	
	static unordered_map<string, Mesh*> allImportedMeshes;
	void setMesh(vector<GLfloat>& vertices, vector<GLuint>& indices, int sizeOfVertex);
};

#endif