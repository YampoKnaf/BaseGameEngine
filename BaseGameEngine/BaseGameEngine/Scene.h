#ifndef __SCENE__H
#define __SCENE__H

#include "Camera.h"
#include <string>

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
private:
	vector<Object> m_allObjects;
	unordered_map<string, vector<Object*>> m_layers;
	vector<Camera*> m_cameras;
	vector<Screen*> m_screens;
};
#endif

