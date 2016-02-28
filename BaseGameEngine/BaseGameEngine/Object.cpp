#include "Object.h"
int Object::id_gen = 0;

Object::Object(Material * material, Mesh * mesh, Component* component):m_material(material),m_mesh(mesh),m_transform(this)
{
	if (component != nullptr)
		AddComponent(component);
	m_id = id_gen++;
	m_name = "Object" + (char)('0' + m_id);
}

vector<Component*> Object::GetAllComponents()
{
	return vector<Component*>(m_components);
}

Mesh* Object::getMesh()
{
	return this->m_mesh;
}

Object::Object(Material * material, Mesh * mesh, string name, Component * component):Object(material , mesh , component)
{
	this->m_name = name;
}

Object::Object(Component * component):Object(nullptr , nullptr , component){}

Object::Object(string name):m_transform(this)
{
	this->m_name = name;
}

Object::Object() : m_transform(this)
{
	m_name = "Object" + (char)('0' + m_id);
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

Transform & Object::getTransform()
{
	return m_transform;
}

Material* Object::GetMaterial()
{
	return m_material;
}

Mesh * Object::setMesh(Mesh * mesh)
{
	return this->m_mesh = mesh;
}

Material * Object::SetMaterial(Material * material)
{
	return this->m_material = material;
}

Component * Object::AddComponent(Component * component)
{
	int index = FindElementInVector(m_components, component);
	if (index != -1)
		return component;
	m_components.push_back(component);
	SetComponent(component, this, &this->m_transform);
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
	return m_transform.GetChild(index)->object;
}

Object * Object::AddChild(Object * child)
{
	m_transform.AddChild(&child->m_transform);
	return child;
}

Object * Object::setParent(Object * parent)
{
	m_transform.parent = &parent->m_transform;
	return parent;
}

Object * Object::getParent()
{
	if (transform.parent)
		return transform.parent->object;
	return nullptr;
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
	if (!object->m_mesh || !object->m_material)
		return;
	object->m_material->Bind(viewMatrix, object->m_transform.GetModelMatrix());
	object->m_mesh->Draw();
}
