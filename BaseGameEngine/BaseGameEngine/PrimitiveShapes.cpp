#include "Mesh.h"

Mesh::Mesh(ShapesTypes type, int resX, int resY)
{
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	m_hasNormals = true;
	m_numOfUVChannels = 0;
	m_hasTangens = false;
	m_numOfColorChannel = 0;
	m_hasIndices = true;

	vertices = {
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	indices = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};
	
	setMesh(vertices, indices, 3);
}