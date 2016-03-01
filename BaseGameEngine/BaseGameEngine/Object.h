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
	Object(Material* materia, Mesh* mesh, string name);
	Object();
	Object(string name);

	void Start();
	void Update(double deltaTime);

	PROPERTY(getMesh, setMesh) Mesh* mesh;
	PROPERTY(getTransform) Transform& transform;
	PROPERTY(getParent, setParent) Object* parent;
	
	vector<Component*> GetAllComponents();
	Material* GetMaterial();
	
	Material* SetMaterial(Material* material);
	Component* RemoveComponent(Component* component);

	template<class Comp>
	Comp* AddComponent()
	{
		Comp* component = new Comp();
		m_components.push_back(component);
		SetComponent(component, this, &this->m_transform);
		return component;
	}


	Object* GetChild(int index);
	Object* AddChild(Object* child);
	
	bool operator==(Object& object);
	Transform& getTransform();
	Mesh* setMesh(Mesh* mesh);
	Mesh* getMesh();
	Object* setParent(Object* parent);
	Object* getParent();
private:	
	Transform m_transform;
	Material* m_material = nullptr;
	Mesh* m_mesh = nullptr;
	vector<Component*> m_components;
	string m_name;
	int m_id;
	static int id_gen;
	friend void renderer(Object* object, mat4 viewMatrix);
};
#endif

