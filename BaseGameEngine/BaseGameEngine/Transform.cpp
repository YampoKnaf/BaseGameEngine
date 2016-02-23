#include "Transform.h"

Transform::Transform(vec3 position, vec3 scale, quat rotation) :position(position), scale(scale), rotation(rotation) {}

vec3 Transform::Translate(vec3 delta)
{
	position += delta;
	return position;
}

vec3 Transform::TranslateLocal(vec3 delta)
{
	mat4 modelMat = GetModelMatrix();
	delta = vec3(modelMat * vec4(delta , 0));
	position += delta;
	return position;
}

quat Transform::Rotate(vec3 axis, GLfloat angle)
{
	rotation = rotate(rotation, angle, axis);
	return rotation;
}

quat Transform::LocalRotate(vec3 axis, GLfloat angle)
{
	mat4 modelMat = GetModelMatrix();
	axis = vec3(modelMat * vec4(axis, 0));
	rotation = rotate(rotation, angle, axis);
	return rotation;
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
	mat4 matrix = translate(mat4(), position);
	matrix *= glm::scale(matrix, scale);
	matrix *= mat4(rotation);
	return matrix;
}
