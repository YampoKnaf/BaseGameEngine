#ifndef __ANIME_MATERIAL_H
#define __ANIME_MATERIAL_H

#include "Material.h"

class AnimatedMat : public Material
{
public:
	AnimatedMat();
	AnimatedMat(aiMaterial* material, string directory);//to support import mesh
	virtual void Bind(mat4 view, mat4 model);
};

#endif