#ifndef __AD_DIFFUSE_MAT__H
#define __AD_DIFFUSE_MAT__H

#include "Material.h"

class AdDiffuseMat : public Material
{
public:
	AdDiffuseMat();
	AdDiffuseMat(aiMaterial* material, string directory);//to support import mesh

	Texture* SetDiffuseMap(Texture* texture);
	Texture* SetNormalMap(Texture* texture);

	virtual void Bind(mat4 view, mat4 model);

private:
	Texture* diffuse = nullptr;
	Texture* normalMap = nullptr;
};
#endif

