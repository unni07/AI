#pragma once
#include "gameobject.h"
class utility
{
public:
	utility();
	~utility();

	static GameObject * findTargetinRadius(GameObject * me, unsigned int target, float radius);
	static float distanceBetween(GameObject*,GameObject*);
	static bool isNear(D3DXVECTOR3 &pos, D3DXVECTOR3 &target, float nearDist = 1.f / 100.f);
};