#include "BasicTexMat.h"

BasicTexMat::BasicTexMat()
{
	shader = Shader::GetShader("Shaders/BasicTexVex.vex", "Shaders/þþBasicTexFreg.freg");
}

BasicTexMat::BasicTexMat(aiMaterial * material , string directory):BasicTexMat()
{
	texture = loadTexture(material, aiTextureType_DIFFUSE, directory);
}

void BasicTexMat::Bind(mat4 view, mat4 model)
{
	shader->Use();
	bindViewAndModelMatrix(view, model);
	bindTexture(texture, "diffuse", 0);
}

void BasicTexMat::SetTexture(Texture * texture)
{
	this->texture = texture;
}
