#ifndef __OBJECT__H
#define __OBJECT__H

#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Component.h"
#include "HelperClass.h"

class Object
{
public:
	Object(Material* material = nullptr, Mesh* mesh = nullptr);
	
	void Start();
	void Update(double deltaTime);

	Transform& GetTransform();
	Mesh* SetMesh(Mesh* mesh);
	Material* SetMaterial(Material* material);
	Component* AddComponent(Component* component);
	Component* RemoveComponent(Component* component);

private:
	Transform transform;
	Material* material = nullptr;
	Mesh* mesh = nullptr;
	vector<Component*> components;

	friend void renderer(Object* object, mat4 viewMatrix);
};
#endif

