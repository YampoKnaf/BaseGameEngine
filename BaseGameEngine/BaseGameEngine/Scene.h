#ifndef __SCENE__H
#define __SCENE__H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Camera.h"

using namespace std;

class Scene
{
public:
	Scene(Screen* screen);

	void AddObjectToLayer(string layerName, Object object);
	void AddObject(Object object);
	void AddCamera(Camera* camera);
	void UpdateLoop();//start the while loop
	void AddScreen(Screen* screen);//supprt more then one screen

	template<class Mat>
	void LoadFile(string fileName)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return;
		}

		string directory = fileName.substr(0, fileName.find_last_of('/'));
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh* mesh = new Mesh(scene->mMeshes[i]);
			int matIndex = scene->mMeshes[i]->mMaterialIndex;
			Mat* mat = new Mat(scene->mMaterials[matIndex]);
			Object object(mat, mesh);
			AddObject(object);
		}
	}

private:
	vector<Object> m_allObjects;
	unordered_map<string, vector<unsigned int>> m_layers;
	vector<Camera*> m_cameras;
	vector<Screen*> m_screens;
};
#endif

