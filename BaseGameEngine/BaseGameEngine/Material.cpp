#include "Material.h"

string getProperyName(string baseName)
{
	stringstream str;
	str << "material." << baseName;
	return str.str();
}

void Material::bindTexture(Texture * texture, string textureName , GLuint index)
{
	texture->Bind(index, textureName, shader->GetShaderId());
}

void Material::bindFloat(GLfloat input, string floatName)
{
	GLint floatLoc = glGetUniformLocation(shader->GetShaderId(), getProperyName(floatName).c_str());
	glUniform1f(floatLoc, input);
}

void Material::bindVector2(vec2 vector2, string vectorName)
{
	GLint vectorLoc = glGetUniformLocation(shader->GetShaderId(), getProperyName(vectorName).c_str());
	glUniform2f(vectorLoc, vector2.x , vector2.y);
}

void Material::bindVector3(vec3 vector3, string vectorName)
{
	GLint vectorLoc = glGetUniformLocation(shader->GetShaderId(), getProperyName(vectorName).c_str());
	glUniform3f(vectorLoc, vector3.x, vector3.y , vector3.z);
}

void Material::bindVector4(vec4 vector4, string vectorName)
{
	GLint vectorLoc = glGetUniformLocation(shader->GetShaderId(), getProperyName(vectorName).c_str());
	glUniform4f(vectorLoc, vector4.x, vector4.y , vector4.z , vector4.w);
}
