#ifndef __MATERIAL
#define __MATERIAL

#include "glm\glm.hpp"

#include "Shader.h"
#include "Texture.h"

using namespace glm;

class Material
{
public:
	virtual void Bind() = 0;

protected:
	Shader* shader;

	//Help to bind the properties
	void bindTexture(Texture* texture, string textureName , GLuint index);
	void bindFloat(GLfloat input, string floatName);
	void bindVector2(vec2 vector2, string vectorName);
	void bindVector3(vec3 vector3, string vectorName);
	void bindVector4(vec4 vector4, string vectoiName);
};
#endif
