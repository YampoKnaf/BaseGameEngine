#ifndef __TRANSFORM__H
#define __TRANSFORM__H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>

#include "HelperClass.h"

using namespace glm;
using namespace std;

class Object;

class Transform
{
public:
	Transform(Object* object, vec3 position = vec3(0) , vec3 scale = vec3(1), quat rotation = quat(0 , 0 , 0 , 1));
	
	vec3 Position;
	vec3 Scale;
	quat Rotation;

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

	PROPERTY(GetUp) vec3 up;
	PROPERTY(GetRight) vec3 right;
	PROPERTY(GetForward) vec3 forward;
	PROPERTY(getParent, put = setParent)Transform* parent;

	mat4 GetModelMatrix();
	
	Transform* GetChild(int index);
	Transform* AddChild(Transform* child);
	Object* object;
	
	void setParent(Transform* parent);
	Transform* getParent();
private:
	Transform* m_parent = nullptr;
	vector<Transform*> children;
	
};

#endif

