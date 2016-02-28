#ifndef __BASIC_TEX_MAT__H
#define __BASIC_TEX_MAT__H

#include "Material.h"

class BasicTexMat :public Material
{
public:
	BasicTexMat();
	BasicTexMat(aiMaterial* material, string directory);
	virtual void Bind(mat4 view, mat4 model);
	virtual vector<Texture*> GetAllTextures();
	void SetTexture(Texture* texture);
private:
	Texture* texture;
};
#endif

