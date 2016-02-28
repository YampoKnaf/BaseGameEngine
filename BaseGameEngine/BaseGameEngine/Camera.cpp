#include "Camera.h"

int Camera::id_gen = 0;

Camera::Camera(GLfloat viewPortSizeX, GLfloat viewPortSizeY, GLfloat viewPortPosX, GLfloat viewPortPosY):
													m_viewPortSize(viewPortSizeX , viewPortSizeY),m_viewPortPos(viewPortPosX , viewPortPosY)
{
	m_id = id_gen++;
	m_layers.push_back("main");
}

void Camera::Renderer(vector<unsigned int>& layer , vector<Object*>& allObjects , Screen* screen)
{
	int width = screen->GetWidth(), height = screen->GetHeight();
	glViewport(width * (GLint)m_viewPortPos.x, height * (GLint)m_viewPortPos.y, width * (GLint)m_viewPortSize.x, height * (GLint)m_viewPortSize.y);
	mat4 view = GetViewMatrix(screen);
	for (unsigned int index : layer)
		renderer(allObjects[index], view);
}

vector<string> Camera::GetAllLayers()
{
	return vector<string>(m_layers);
}

void Camera::AddLayer(string layerName)
{
	m_layers.push_back(layerName);
}

bool Camera::operator==(Camera & camera)
{
	return m_id == camera.m_id;
}

void Camera::setViewPortSize(vec2 size)
{
	if (size.x < 0 || size.y < 0 || size.x > 1 || size.y > 1)
		return;
	m_viewPortSize = size;
}

vec2 Camera::getViewPortSize()
{
	return m_viewPortSize;
}

void Camera::setViewPortPos(vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x > 1 || pos.y > 1)
		return;
	m_viewPortPos = pos;
}

vec2 Camera::getViewPortPos()
{
	return m_viewPortPos;
}

mat4 Camera::GetViewMatrix(Screen* screen)
{
	mat4 projection = glm::perspective(45.f, (screen->GetWidth() * m_viewPortSize.x) / (screen->GetWidth() * m_viewPortSize.y), 0.1f, 1000.f);
	return projection * lookAt(transform->Position, transform->Position + transform->GetForward(), transform->GetUp());
}

void Camera::Start(){}
void Camera::Update(double deltaTime) {}
