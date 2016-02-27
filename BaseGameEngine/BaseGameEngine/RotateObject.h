#ifndef __ROTATE_OBJECT__H
#define __ROTATE_OBJECT__H

#include "Component.h"
class RotateObject : public Component
{
public:
	virtual void Start();
	virtual void Update(double deltaTime);
};
#endif

