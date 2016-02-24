#ifndef __OBJECT__H
#define __OBJECT__H

#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Component.h"

class Object
{
public:
	Object(Material* material = nullptr, Mesh* mesh = nullptr);

private:
	Transform transform;
	Material* material = nullptr;
	Mesh* mesh = nullptr;
	vector<Component*> components;

	friend void renderer(Object* object, mat4 viewMatrix);
};
#endif

