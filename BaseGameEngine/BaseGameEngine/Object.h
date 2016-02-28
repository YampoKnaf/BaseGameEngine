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
	Object(Material* material = nullptr, Mesh* mesh = nullptr , Component* component = nullptr);
	Object(Material* materia, Mesh* mesh, string name , Component* component);
	Object(Component* component);
	Object(string name);
	Object();
	void Start();
	void Update(double deltaTime);

	__declspec(property(get = getMesh, put = getMesh)) Mesh* mesh;
	__declspec(property(get = getTransform)) Transform& transform;
	__declspec(property(get = getParent, put = getParent)) Object* parent;
	
	vector<Component*> GetAllComponents();
	Material* GetMaterial();
	
	Material* SetMaterial(Material* material);
	Component* AddComponent(Component* component);
	Component* RemoveComponent(Component* component);

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

