#include "Transform.h"

Transform::Transform(Object* object ,vec3 position, vec3 scale, quat rotation) :Position(position), Scale(scale), Rotation(rotation) , object(object) {}

vec3 Transform::Translate(vec3 delta)
{
	Position += delta;
	return Position;
}

vec3 Transform::TranslateLocal(vec3 delta)
{
	mat4 modelMat = GetModelMatrix();
	delta = vec3(modelMat * vec4(delta , 0));
	Position += delta;
	return Position;
}

quat Transform::Rotate(vec3 axis, GLfloat angle)
{
	Rotation = normalize(rotate(Rotation, angle, axis));
	return Rotation;
}

quat Transform::LocalRotate(vec3 axis, GLfloat angle)
{
	mat4 modelMat = GetModelMatrix();
	axis = vec3(modelMat * vec4(axis, 0));
	Rotation = normalize(rotate(Rotation, angle, axis));
	return Rotation;
}

vec3 Transform::GetForward()
{
	mat4 modelMat = GetModelMatrix();
	return normalize(vec3(modelMat * vec4(0, 0, 1, 0)));
}

vec3 Transform::GetUp()
{
	mat4 modelMat = GetModelMatrix();
	return normalize(vec3(modelMat * vec4(0, 1, 0, 0)));
}

vec3 Transform::GetRight()
{
	mat4 modelMat = GetModelMatrix();
	return normalize(vec3(modelMat * vec4(1, 0, 0, 0)));
}

mat4 Transform::GetModelMatrix()
{
	mat4 matrix = translate(mat4(), Position);
	matrix *= glm::scale(matrix, Scale);
	matrix *= mat4(Rotation);
	if (m_parent != nullptr)
		return m_parent->GetModelMatrix() * matrix;
	return matrix;
}

void Transform::setParent(Transform * parent)
{
	this->m_parent = parent;
	parent->AddChild(this);
}

Transform * Transform::getParent()
{
	return m_parent;
}

Transform * Transform::GetChild(int index)
{
	if (index < 0 || index >= (int)children.size())
		throw "Index Is Out Of Bounds";
	return children[index];
}

Transform * Transform::AddChild(Transform * child)
{
	if (child == nullptr)
		return child;
	
	child->m_parent = this;
	
	int index = FindElementInVector(children, child);
	if (index != -1)
		return child;
	children.push_back(child);
	return child;
}
