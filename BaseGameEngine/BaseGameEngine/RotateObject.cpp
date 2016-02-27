#include "RotateObject.h"

void RotateObject::Start()
{
	//transform->Rotate(vec3(1, 0, 0), -3.14);
}

void RotateObject::Update(double deltaTime)
{
	transform->Rotate(vec3(0, 1, 0), deltaTime);
}
