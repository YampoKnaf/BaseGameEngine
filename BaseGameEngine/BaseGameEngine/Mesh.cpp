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

bool Mesh::HasBonse()
{
	return m_hasBones;
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
	int index = 1;
	if (m_numOfUVChannels = mesh->GetNumUVChannels())
	{
		sizeOfVertex += 2 * m_numOfUVChannels;
		index++;
	}
	if (m_hasNormals = mesh->HasNormals())
	{
		sizeOfVertex += 3;
		index++;
	}
	if (m_hasTangens = mesh->HasTangentsAndBitangents())
	{
		sizeOfVertex += 3;
		index++;
	}
	if (m_numOfColorChannel = mesh->GetNumColorChannels())
	{
		sizeOfVertex += 4 * m_numOfColorChannel;
		index++;
	}
	m_hasIndices = mesh->HasFaces();
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
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
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace* face = mesh->mFaces + i;
			for (unsigned int indexNum = 0; indexNum < face->mNumIndices;indexNum++)
			{
				indices.push_back(face->mIndices[indexNum]);
			}
		}
	}
	setMesh(vertices, indices, sizeOfVertex);
	
	//vertex bones init
	if (m_hasBones = mesh->HasBones())
		SetBonesToMesh(mesh, index);
}

void Mesh::SetBonesToMesh(aiMesh * mesh , int index)
{
	vector<GLuint> boneIds;
	vector<GLfloat> boneWeight;
	boneIds.resize(mesh->mNumVertices * 4);
	boneWeight.resize(mesh->mNumVertices * 4);
	for (unsigned int i = 0; i < mesh->mNumBones; i++)
	{
		for (int j = 0; j < mesh->mBones[i]->mNumWeights ; j++)
		{
			int vertexId = mesh->mBones[i]->mWeights[j].mVertexId * 4;
			while (boneIds[vertexId] != 0)
				vertexId++;
			boneIds[vertexId] = i;
			boneWeight[vertexId] = mesh->mBones[i]->mWeights[j].mWeight;
		}
	}
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, boneIds.size() * sizeof(GLuint), &boneIds[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index++, 4, GL_UNSIGNED_INT, GL_FALSE,sizeof(GLuint) * 4, (GLvoid*)0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, boneWeight.size() * sizeof(GLfloat), &boneWeight[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index++, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*)0);

	glBindVertexArray(0);
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