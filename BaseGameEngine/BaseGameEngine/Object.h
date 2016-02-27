#ifndef __OBJECT__H
#define __OBJECT__H

#include "Transform.h"
#include "Mesh.h"
#include "materials\Material.h"
#include "Component.h"
#include "HelperClass.h"

class Object
{
public:
	Object(Material* material = nullptr, Mesh* mesh = nullptr , Component* component = nullptr);
	Object(Component* component);

	void Start();
	void Update(double deltaTime);

	Transform& GetTransform();
	Mesh* SetMesh(Mesh* mesh);
	Material* SetMaterial(Material* material);
	Component* AddComponent(Component* component);
	Component* RemoveComponent(Component* component);

	bool operator==(Object& object);
private:
	Transform transform;
	Material* material = nullptr;
	Mesh* mesh = nullptr;
	vector<Component*> m_components;
	int m_id;
	static int id_gen;
	friend void renderer(Object* object, mat4 viewMatrix);
};
#endif

