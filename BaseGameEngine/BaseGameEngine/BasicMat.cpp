#include "BasicMat.h"

BasicMat::BasicMat()
{
	shader = Shader::GetShader("Shaders/BasicVertex.vex", "Shaders/BasicFregment.freg");
}

BasicMat::BasicMat(aiMaterial * material) :BasicMat()
{
	
}

void BasicMat::Bind(mat4 view, mat4 model)
{
	bindViewAndModelMatrix(view, model);
	shader->Use();
}
