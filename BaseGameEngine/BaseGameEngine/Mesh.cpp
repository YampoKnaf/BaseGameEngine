#include "Mesh.h"

#define SET_VERTEX_PROPERTY(SIZE_OF_PROPERTY , OFFSET , INDEX) {glEnableVertexAttribArray(INDEX);\
																glVertexAttribPointer(INDEX++, SIZE_OF_PROPERTY, GL_FLOAT, GL_FALSE, \
																				sizeof(GLfloat) * sizeOfVertex, (GLvoid*)(OFFSET * sizeof(GLfloat)));\
																OFFSET += SIZE_OF_PROPERTY;}

unordered_map<string, Mesh*> Mesh::allImportedMeshes;

int Mesh::NumOfUVChannels()
{
	return m_numOfUVChannels;
}

int Mesh::NumOfColorChannel()
{
	return m_numOfColorChannel;
}

bool Mesh::HasNormals()
{
	return m_hasNormals;
}

bool Mesh::HasTangens()
{
	return m_hasTangens;
}

bool Mesh::HasIndices()
{
	return m_hasIndices;
}

void Mesh::Draw()
{
	glBindVertexArray(m_VAO);
	if (m_hasIndices)
		glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_size);
	glBindVertexArray(0);
}

Mesh::Mesh(aiMesh * mesh)
{
	vector<GLfloat> vertices;
	vector<GLuint> indices;
	int sizeOfVertex = 3;
	if (m_numOfUVChannels = mesh->GetNumUVChannels())
	{
		sizeOfVertex += 2 * m_numOfUVChannels;
	}
	if (m_hasNormals = mesh->HasNormals())
	{
		sizeOfVertex += 3;
	}
	if (m_hasTangens = mesh->HasTangentsAndBitangents())
	{
		sizeOfVertex += 3;
	}
	if (m_numOfColorChannel = mesh->GetNumColorChannels())
	{
		sizeOfVertex += 4 * m_numOfColorChannel;
	}
	m_hasIndices = mesh->HasFaces();
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		if (m_hasNormals)
		{
			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);
		}

		
		for (int j = 0; j < m_numOfUVChannels; j++)
		{
			vertices.push_back(mesh->mTextureCoords[j][i].x);
			vertices.push_back(mesh->mTextureCoords[j][i].y);
		}

		if (m_hasTangens)
		{
			vertices.push_back(mesh->mTangents[i].x);
			vertices.push_back(mesh->mTangents[i].y);
			vertices.push_back(mesh->mTangents[i].z);
		}

		for (int j = 0; j < m_numOfColorChannel; j++)
		{
			vertices.push_back(mesh->mColors[j][i].r);
			vertices.push_back(mesh->mColors[j][i].g);
			vertices.push_back(mesh->mColors[j][i].b);
			vertices.push_back(mesh->mColors[j][i].a);
		}
	}

	if (m_hasIndices)
	{
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace* face = mesh->mFaces + i;
			for (int indexNum = 0; indexNum < face->mNumIndices;indexNum++)
			{
				indices.push_back(face->mIndices[indexNum]);
			}
		}
	}
	setMesh(vertices, indices, sizeOfVertex);

}

void Mesh::setMesh(vector<GLfloat>& vertices, vector<GLuint>& indices, int sizeOfVertex)
{
	glGenVertexArrays(1, &m_VAO);

	m_size = vertices.size() / sizeOfVertex;

	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	if (m_hasIndices)
	{
		m_size = indices.size();
		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		
	}

	int index = 0;
	int offSet = 0;
	// Vertex Positions
	SET_VERTEX_PROPERTY(3, offSet, index);
	// Vertex Normals
	if (m_hasNormals)
		SET_VERTEX_PROPERTY(3, offSet, index);

	// Vertex Texture Coords
	if (m_numOfUVChannels)
		SET_VERTEX_PROPERTY(2 * m_numOfUVChannels, offSet, index);

	// Vertex Tangen
	if (m_hasTangens)
		SET_VERTEX_PROPERTY(3, offSet, index);

	// Vertex Color
	if (m_numOfColorChannel)
		SET_VERTEX_PROPERTY(4 * m_numOfColorChannel, offSet, index);

	glBindVertexArray(0);
}

Mesh * Mesh::GetMesh(aiMesh * mesh, string fileName , int index)
{
	stringstream meshName;
	meshName << fileName << "::" << index;
	fileName = meshName.str();
	Mesh** selectedMesh;
	if (FindInUnorderMapValueByKey(Mesh::allImportedMeshes, fileName, &selectedMesh))
	{
		return *selectedMesh;
	}
	Mesh* newMesh = new Mesh(mesh);
	allImportedMeshes.insert({ fileName , newMesh });
	return newMesh;
}