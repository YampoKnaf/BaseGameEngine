#include "Scene.h"

Scene::Scene(Screen* screen)
{
	m_screens.push_back(screen);
}

void Scene::AddObjectToLayer(string layerName, Object* object)
{
	unsigned int objIndex;
	int index = FindElementInVector(m_allObjects, object);
	if (index == -1)
	{
		m_allObjects.push_back(object);
		objIndex = m_allObjects.size() - 1;
	}
	else
	{
		objIndex = index;
	}
	
	vector<unsigned int>* layerObjects;
	if(FindInUnorderMapValueByKey(m_layers, layerName , &layerObjects))
	{
		index = FindElementInVector(*layerObjects, objIndex);
		if (index == -1)
			layerObjects->push_back(objIndex);
		else
			return;
	}
	else
	{
		m_layers.insert({ layerName , vector<unsigned int>(1 , objIndex) });
	}
}

void Scene::AddObject(Object* object)
{
	AddObjectToLayer("main", object);
}

void Scene::AddCamera(Camera* camera)
{
	int index = FindElementInVector(m_cameras, camera);
	if (index != -1)
		return;
	m_cameras.push_back(camera);
}

void Scene::UpdateLoop()
{
	double lastTime = 0;
	glfwSetTime(0);
	for (unsigned int i = 0; i < m_allObjects.size(); i++)
	{
		m_allObjects[i]->Start();
	}

	while (true)
	{
		bool shouldBeClose = true;
		for (Screen* screen : m_screens)
		{
			if (!screen->ShouldClose())
				shouldBeClose = false;
		}
		if (shouldBeClose)
			break;
		glfwPollEvents();
		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;
		lastTime = currentTime;

		for (unsigned int i = 0; i < m_allObjects.size(); i++)
		{
			m_allObjects[i]->Update(delta);
		}
		for (Screen* screen : m_screens)
		{
			for (Camera* camera : m_cameras)
			{
				vector<string> layers = camera->GetAllLayers();
				for (string layer : layers)
				{
					vector<unsigned int>* layerObjects;
					if(FindInUnorderMapValueByKey(m_layers , layer , &layerObjects))
						camera->Renderer(*layerObjects , m_allObjects, screen);
				}
			}
			screen->Clear();
		}
	}
	freeAll();
}

void Scene::freeAll()
{
	vector<Mesh*> allMeshes;
	vector<Material*> allMaterials;
	vector<Texture*> allTextures;
	vector<Component*> allComponents;
	for (Object* object : m_allObjects)
	{
		Mesh* mesh = object->mesh;
		if (mesh)
		{
			int index = FindElementInVector(allMeshes, mesh);
			if (index == -1)
				allMeshes.push_back(mesh);
		}
		Material* mat = object->GetMaterial();
		if (mat)
		{
			int index = FindElementInVector(allMaterials, mat);
			if (index == -1)
				allMaterials.push_back(mat);
		}
		vector<Component*> components = object->GetAllComponents();
		for (Component* comp : components)
		{
			int index = FindElementInVector(allComponents, comp);
			if (index == -1)
				allComponents.push_back(comp);
		}

		delete object;
	}
	for (Mesh* mesh : allMeshes)
	{
		delete mesh;
	}
	for (Material* mat : allMaterials)
	{
		vector<Texture*> textures = mat->GetAllTextures();
		for (Texture* tex : textures)
		{
			int index = FindElementInVector(allTextures, tex);
			if (index == -1)
				allTextures.push_back(tex);
		}
		delete mat;
	}
	for (Texture* tex : allTextures)
	{
		delete tex;
	}
	for (Component* comp : allComponents)
	{
		delete comp;
	}
}

void Scene::AddScreen(Screen * screen)
{
	int index = FindElementInVector(m_screens, screen);
	if (index != -1)
		return;
	m_screens.push_back(screen);
}

vector<Object*>& Scene::GetAllObjects()
{
	return m_allObjects;
}




