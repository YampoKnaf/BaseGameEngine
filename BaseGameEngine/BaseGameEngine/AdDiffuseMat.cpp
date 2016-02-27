#include "AdDiffuseMat.h"



AdDiffuseMat::AdDiffuseMat()
{
	shader = Shader::GetShader("Shaders/AdDiffuseVex.vex", "Shaders/AdDiffuseFreg.freg");
}

AdDiffuseMat::AdDiffuseMat(aiMaterial * material, string directory):AdDiffuseMat()
{
	diffuse = loadTexture(material, aiTextureType_DIFFUSE, directory);
	normalMap = loadTexture(material, aiTextureType_NORMALS, directory);
}

Texture * AdDiffuseMat::SetDiffuseMap(Texture * texture)
{
	return this->diffuse = diffuse;
}

Texture * AdDiffuseMat::SetNormalMap(Texture * texture)
{
	return this->normalMap = texture;
}

void AdDiffuseMat::Bind(mat4 view, mat4 model)
{
	shader->Use();
	bindViewAndModelMatrix(view, model);
	BIND_TEXTURE(diffuse, 0);
	BIND_TEXTURE(normalMap , 1);
}
