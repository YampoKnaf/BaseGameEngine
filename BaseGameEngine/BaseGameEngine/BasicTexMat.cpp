#include "BasicTexMat.h"

BasicTexMat::BasicTexMat()
{
	shader = Shader::GetShader("Shaders/BasicTexVex.vex", "Shaders/þþBasicTexFreg.freg");
}

BasicTexMat::BasicTexMat(aiMaterial * material , string directory):BasicTexMat()
{
	aiString pathFile;
	int num = material->GetTextureCount(aiTextureType_DIFFUSE);
	material->GetTexture(aiTextureType_DIFFUSE, 0, &pathFile);
	string fileName(pathFile.C_Str());
	fileName = directory + '/' + fileName;
	texture = Texture::GetTexture("./models/nanosuit2/tex/body_showroom_spec.png");
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
