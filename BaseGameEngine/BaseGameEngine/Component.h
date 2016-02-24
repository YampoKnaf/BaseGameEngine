#ifndef __COMPONENT__H
#define __COMPONENT__H

#include "Transform.h"
class Object;

class Component
{
public:
	virtual void Start() = 0;
	virtual void Update(double deltaTime) = 0;
protected:
	Transform* transform;
	Object* object;

private:
	friend void SetComponent(Component* component, Object* object, Transform* transform);
};
#endif

