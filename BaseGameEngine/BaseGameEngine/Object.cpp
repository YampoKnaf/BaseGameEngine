#include "Object.h"

Object::Object(Material * material, Mesh * mesh):material(material),mesh(mesh){}

void Object::Start()
{
	for (Component* comp : components)
		comp->Start();
}

void Object::Update(double deltaTime)
{
	for (Component* comp : components)
		comp->Update(deltaTime);
}

Transform & Object::GetTransform()
{
	return transform;
}

Mesh * Object::SetMesh(Mesh * mesh)
{
	return this->mesh = mesh;
}

Material * Object::SetMaterial(Material * material)
{
	return this->material = material;
}

Component * Object::AddComponent(Component * component)
{
	int index = FindElementInVector(components, component);
	if (index != -1)
		return component;
	components.push_back(component);
	SetComponent(component, this, &this->transform);
	return component;
}

Component * Object::RemoveComponent(Component * component)
{
	int index = FindElementInVector(components, component);
	if (index == -1)
		return nullptr;
	components.erase(components.begin() + index);
	return component;
}

void SetComponent(Component* component, Object* object, Transform* transform)
{
	component->object = object;
	component->transform = transform;
}
