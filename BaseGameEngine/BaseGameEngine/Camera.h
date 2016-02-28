#ifndef __CAMERA__H
#define __CAMERA__H

#include <vector>
#include <array>
#include "Component.h"
#include "Screen.h"
#include "Object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Camera :public Component
{
public:
	//view port should be between 0 t0 1
	Camera(GLfloat viewPortSizeX = 1, GLfloat viewPortSizeY = 1 , GLfloat viewPortPosX = 0 , GLfloat viewPortPosY = 0);

	void Renderer(vector<unsigned int>& layer, vector<Object*>& allObjects, Screen * screen);
	vector<string> GetAllLayers();
	void AddLayer(string layerName);

	bool operator==(Camera& camera);

	__declspec(property(get = getViewPortSize, put = setViewPortSize))vec2 viewPortSize;
	__declspec(property(get = getViewPortPos, put = setViewPortPos))vec2 viewPortPos;

	void setViewPortSize(vec2 size);
	vec2 getViewPortSize();

	void setViewPortPos(vec2 pos);
	vec2 getViewPortPos();

private:
	mat4 GetViewMatrix(Screen* screen);
	virtual void Start();
	virtual void Update(double deltaTime);
	vector<string> m_layers;
	vec2 m_viewPortSize;
	vec2 m_viewPortPos;

	int m_id;
	static int id_gen;
	friend void renderer(Object* object, mat4 viewMatrix);
};
#endif

