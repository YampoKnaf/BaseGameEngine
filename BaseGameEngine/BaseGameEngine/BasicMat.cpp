#include "BasicMat.h"

BasicMat::BasicMat()
{
	shader = Shader::GetShader("Shaders/BasicVertex.vex", "Shaders/BasicFregment.freg");
}

void BasicMat::Bind(mat4 view, mat4 model)
{
	shader->Use();
}
