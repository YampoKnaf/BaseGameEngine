#include "Camera.h"

int Camera::id_gen = 0;

Camera::Camera(GLfloat viewPortSizeX, GLfloat viewPortSizeY, GLfloat viewPortPosX, GLfloat viewPortPosY):
													viewPortSize(viewPortSizeX , viewPortSizeY),viewPortPos(viewPortPosX , viewPortPosY)
{
	m_id = id_gen++;
	layers.push_back("main");
}

void Camera::Renderer(vector<unsigned int>& layer , vector<Object*>& allObjects , Screen* screen)
{
	int width = screen->GetWidth(), height = screen->GetHeight();
	glViewport(width * viewPortPos.x, height * viewPortPos.y, width * viewPortSize.x, height * viewPortSize.y);
	mat4 view = GetViewMatrix(screen);
	for (unsigned int index : layer)
		renderer(allObjects[index], view);
}

vector<string> Camera::GetAllLayers()
{
	return vector<string>(layers);
}

void Camera::AddLayer(string layerName)
{
	layers.push_back(layerName);
}

bool Camera::operator==(Camera & camera)
{
	return m_id == camera.m_id;
}

mat4 Camera::GetViewMatrix(Screen* screen)
{
	mat4 projection = glm::perspective(45.f, (screen->GetWidth() * viewPortSize.x) / (screen->GetWidth() * viewPortSize.y), 0.1f, 1000.f);
	return projection * lookAt(transform->Position, transform->Position + transform->GetForward(), transform->GetUp());
}

void Camera::Start(){}
void Camera::Update(double deltaTime) {}
