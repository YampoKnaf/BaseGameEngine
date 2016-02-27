#include "Material.h"

string getProperyName(string baseName)
{
	stringstream str;
	str << "material." << baseName;
	return str.str();
}

void Material::bindTexture(Texture * texture, string textureName , GLuint index)
{
	if(texture)
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

void Material::bindMatrix4x4(mat4 matrix, string matrixName)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderId(), matrixName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Material::bindViewAndModelMatrix(mat4 view, mat4 model)
{
	bindMatrix4x4(view, "view");
	bindMatrix4x4(model, "model");
}

char getReplaceChar(aiTextureType texType)
{
	switch (texType)
	{
	case aiTextureType_SPECULAR:
		return 's';
		break;
	case aiTextureType_AMBIENT:
		return 'a';
		break;
	case aiTextureType_EMISSIVE:
		return 'e';
		break;
	case aiTextureType_HEIGHT:
		return 'h';
		break;
	case aiTextureType_NORMALS:
		return 'n';
		break;
	case aiTextureType_SHININESS:
		return 's';
		break;
	case aiTextureType_OPACITY:
		return 'o';
		break;
	case aiTextureType_DISPLACEMENT:
		return 'd';
		break;
	case aiTextureType_REFLECTION:
		return 'r';
		break;
	default:
		return 'd';
		break;
	}
}

Texture * Material::loadTexture(aiMaterial * material, aiTextureType textureType , string directory)
{
	aiString path;
	material->GetTexture(textureType, 0, &path);
	string fileName = directory + '/' + string(path.C_Str());
	Texture* texture = Texture::GetTexture(fileName);
	if (texture != nullptr)
		return texture;
	if(textureType != aiTextureType_DIFFUSE)
	{
		if (loadTexture(material, aiTextureType_DIFFUSE, directory))
		{
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, 0 ,&str);
			string fileName(str.C_Str());
			fileName[fileName.find_last_of('d')] = getReplaceChar(textureType);
			texture = Texture::GetTexture(directory + '/' + fileName);
		}
	}
	return texture;
}
