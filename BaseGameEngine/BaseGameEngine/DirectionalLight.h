#ifndef __DIRECTIONAL_LIGHT__H
#define __DIRECTIONAL_LIGHT__H

#include <GL\glew.h>
#include <glm\glm.hpp>

using namespace glm;

class DirectionalLight
{
public:
	DirectionalLight(vec3 direction = vec3(0 , 1 , 0) , vec3 color = vec3(1));
	void Bind(GLuint shaderId);
private:
	vec3 m_direction, color;
};
#endif

