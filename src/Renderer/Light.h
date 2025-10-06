#ifndef LIGHT_H
#define LIGHT_H

#include <mdm.h>

struct Light
{
	mdm::Vector::Vec3 pos;
	mdm::Vector::Vec3 color;
	float intensity;
};

#endif // !LIGHT_H
