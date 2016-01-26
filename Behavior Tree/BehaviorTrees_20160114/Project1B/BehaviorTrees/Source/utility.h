#pragma once
#include "gameobject.h"
class utility
{
public:
	utility();
	~utility();

	static GameObject * findTargetinRadius(GameObject * me, unsigned int target, float radius);
};