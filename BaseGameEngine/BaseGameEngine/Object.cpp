#include "Object.h"
int Object::id_gen = 0;

Object::Object(Material * material, Mesh * mesh, Component* component):material(material),mesh(mesh),transform(this)
{
	if (component != nullptr)
		AddComponent(component);
	m_id = id_gen++;
	name = "Object" + (char)('0' + m_id);
}

vector<Component*> Object::GetAllComponents()
{
	return vector<Component*>(m_components);
}

Mesh* Object::GetMesh()
{
	return this->mesh;
}

Object::Object(Material * material, Mesh * mesh, string name, Component * component):Object(material , mesh , component)
{
	this->name = name;
}

Object::Object(Component * component):Object(nullptr , nullptr , component){}

Object::Object(string name):transform(this)
{
	this->name = name;
}

Object::Object() : transform(this)
{
	name = "Object" + (char)('0' + m_id);
}

void Object::Start()
{
	for (Component* comp : m_components)
		comp->Start();
}

void Object::Update(double deltaTime)
{
	for (Component* comp : m_components)
		comp->Update(deltaTime);
}

Transform & Object::GetTransform()
{
	return transform;
}

Material* Object::GetMaterial()
{
	return material;
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
	int index = FindElementInVector(m_components, component);
	if (index != -1)
		return component;
	m_components.push_back(component);
	SetComponent(component, this, &this->transform);
	return component;
}

Component * Object::RemoveComponent(Component * component)
{
	int index = FindElementInVector(m_components, component);
	if (index == -1)
		return nullptr;
	m_components.erase(m_components.begin() + index);
	return component;
}

Object * Object::GetChild(int index)
{
	return transform.GetChild(index)->object;
}

Object * Object::AddChild(Object * child)
{
	transform.AddChild(&child->transform);
	return child;
}

Object * Object::SetParent(Object * parent)
{
	transform.SetParent(&parent->transform);
	return parent;
}

bool Object::operator==(Object & object)
{
	return m_id == object.m_id;
}

void SetComponent(Component* component, Object* object, Transform* transform)
{
	component->object = object;
	component->transform = transform;
}

void renderer(Object* object, mat4 viewMatrix)
{
	if (!object->mesh || !object->material)
		return;
	object->material->Bind(viewMatrix, object->transform.GetModelMatrix());
	object->mesh->Draw();
}
