#include "Scene.h"

Scene::Scene(Screen* screen)
{
	m_screens.push_back(screen);
}

void Scene::AddObjectToLayer(string layerName, Object object)
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

void Scene::AddObject(Object object)
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
		m_allObjects[i].Start();
	}

	while (true)
	{
		glfwPollEvents();
		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;
		lastTime = currentTime;

		for (unsigned int i = 0; i < m_allObjects.size(); i++)
		{
			m_allObjects[i].Update(delta);
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
}

void Scene::AddScreen(Screen * screen)
{
	int index = FindElementInVector(m_screens, screen);
	if (index != -1)
		return;
	m_screens.push_back(screen);
}




