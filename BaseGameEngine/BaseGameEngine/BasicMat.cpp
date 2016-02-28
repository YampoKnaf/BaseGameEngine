#include "BasicMat.h"

BasicMat::BasicMat()
{
	shader = Shader::GetShader("Shaders/BasicVertex.vex", "Shaders/BasicFregment.freg");
}

BasicMat::BasicMat(aiMaterial * material, string directory) :BasicMat()
{
	
}

void BasicMat::Bind(mat4 view, mat4 model)
{
	shader->Use();
	bindViewAndModelMatrix(view, model);
}

vector<Texture*> BasicMat::GetAllTextures()
{
	return vector<Texture*>();
}
