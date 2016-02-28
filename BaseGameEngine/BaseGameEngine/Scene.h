#ifndef __SCENE__H
#define __SCENE__H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "HelperClass.h"
#include "Camera.h"

using namespace std;

class Scene
{
public:
	Scene(Screen* screen);

	void AddObjectToLayer(string layerName, Object* object);
	void AddObject(Object* object);
	void AddCamera(Camera* camera);
	void UpdateLoop();//start the while loop
	void AddScreen(Screen* screen);//supprt more then one screen
	vector<Object*>& GetAllObjects();

	template<class Mat>
	Object* LoadFile(string fileName)
	{
		string directory = fileName.substr(0, fileName.find_last_of('/'));
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);

		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
			return nullptr;
		}
	
		string objName = fileName.substr(fileName.find_last_of('/') + 1, fileName.size());
		Object* object = new Object(objName);
		AddObject(object);
		int meshIndex = 0;
		for (unsigned int i = 0; i < scene->mRootNode->mNumChildren; i++)
		{
			Object* child = LoadNode<Mat>(scene, scene->mRootNode->mChildren[i] , directory , objName , &meshIndex);
			object->AddChild(child);
		}
		import.FreeScene();
		return object;
	}


private:
	vector<Object*> m_allObjects;
	unordered_map<string, vector<unsigned int>> m_layers;
	vector<Camera*> m_cameras;
	vector<Screen*> m_screens;

	void freeAll();

	template<class Mat>
	Object* LoadNode(const aiScene* scene, aiNode* node , string directory , string fileName , int* index)
	{
		int meshIndex = node->mMeshes[0];
		Mesh* mesh = Mesh::GetMesh(scene->mMeshes[meshIndex], directory + '/' + fileName , *index);
		(*index)++;
		int matIndex = scene->mMeshes[meshIndex]->mMaterialIndex;
		Mat* mat = new Mat(scene->mMaterials[matIndex], directory);
		Object* object = new Object(mat, mesh);
		Transform& trans = object->GetTransform();
		mat4 matrix = aiMatrix4x4ToMat4(node->mTransformation.Inverse());
		trans.Position = vec3(matrix * vec4(trans.Position , 1));
		trans.Rotation = quat(matrix);
		trans.Scale = vec3(scale(matrix, trans.Scale) * vec4(1));
		AddObject(object);
		for (int i = 0; i < node->mNumChildren; i++)
		{
			Object* child = LoadNode<Mat>(scene, node->mChildren[i] ,directory,fileName , index);
			object->AddChild(object);
		}
		return object;
	}
};
#endif

