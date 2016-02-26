#include "Mesh.h"

Mesh::Mesh(ShapesTypes type, int resX, int resY)
{
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	m_hasNormals = false;
	m_numOfUVChannels = 1;
	m_hasTangens = false;
	m_numOfColorChannel = 0;
	m_hasIndices = true;

	vertices = {
		0.5f,  0.5f, 0.0f  , 0 , 0, // Top Right
		0.5f, -0.5f, 0.0f  , 1 , 0, // Bottom Right
		-0.5f, -0.5f, 0.0f , 1 , 1, // Bottom Left
		-0.5f,  0.5f, 0.0f , 0 , 1, // Top Left 
	};
	indices = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};
	
	setMesh(vertices, indices, 5);
}