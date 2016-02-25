#ifndef __BASIC_MAT__H
#define __BASIC_MAT__H

#include "Material.h"

class BasicMat : public Material
{
public:
	BasicMat();
	virtual void Bind(mat4 view, mat4 model);
};
#endif

