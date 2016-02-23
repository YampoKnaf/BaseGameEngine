#pragma once
#ifndef __TRANSFORM__H
#define __TRANSFORM__H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace glm;

class Transform
{
public:
	Transform(vec3 position = vec3(0) , vec3 scale = vec3(1), quat rotation = quat(0 , 0 , 0 , 1));
	
	vec3 position;
	vec3 scale;
	quat rotation;

	//translate the object base on the world space
	vec3 Translate(vec3 delta);

	//translate the object base on the local space
	vec3 TranslateLocal(vec3 delta);

	//Rotate base on world space
	quat Rotate(vec3 axis, GLfloat angle);

	//Rotate base on local space
	quat LocalRotate(vec3 axis, GLfloat angle);

	vec3 GetForward();
	vec3 GetUp();
	vec3 GetRight();

	mat4 GetModelMatrix();
};

#endif
