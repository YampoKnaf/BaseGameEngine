#include "Scene.h"

Scene::Scene(Screen* screen)
{
	m_screens.push_back(screen);
}

void Scene::AddObjectToLayer(string layerName, Object object)
{
	Object* objAddress;
	int index = FindElementInVector(m_allObjects, object);
	if (index == -1)
	{
		m_allObjects.push_back(object);
		objAddress = &m_allObjects[0] + m_allObjects.size() - 1;
	}
	else
	{
		objAddress = &(m_allObjects[0]) + index;
	}
	vector<Object*>* layerObjects = FindInUnorderMapValueByKey(m_layers, layerName);
	if (layerObjects)
	{
		index = FindElementInVector(*layerObjects, objAddress);
		if (index == -1)
			layerObjects->push_back(objAddress);
		else
			return;
	}
	else
	{
		m_layers.insert({ layerName , vector<Object*>(1 , objAddress) });
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
	for (int i = 0; i < m_allObjects.size(); i++)
	{
		m_allObjects[i].Start();
	}

	while (true)
	{
		glfwPollEvents();
		double currentTime = glfwGetTime();
		double delta = currentTime - lastTime;
		lastTime = currentTime;

		for (int i = 0; i < m_allObjects.size(); i++)
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
					vector<Object*>* layerObjects = FindInUnorderMapValueByKey(m_layers , layer);
					if (layerObjects)
						camera->Renderer(*layerObjects, screen);
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

