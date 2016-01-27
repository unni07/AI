#include "DXUT.h"
#include "utility.h"
#include "database.h"
#include "body.h"

GameObject * utility::findTargetinRadius(GameObject * me, unsigned int target, float radius)
	 {
		 dbCompositionList listZombie;
		 g_database.ComposeList(listZombie, target);
		 dbCompositionList::iterator iter, iterEnd;
		 iter = listZombie.begin();
		 iterEnd = listZombie.end();
		 float distance = 100000.0f;
		 GameObject *go = NULL;
		 while (iter != iterEnd && distance > radius)
		 {
			 D3DXVECTOR3 humanPosition = (*iter)->GetBody().GetPos();
			 auto myPosition = me->GetBody().GetPos();
			 auto vecDistance = humanPosition - myPosition;
			 distance = D3DXVec3Length(&vecDistance);

			 if (distance< radius)
				 go = *iter;

			 iter++;
		 }
		 //attacker = go;
		 return go;
	 }
float utility::distanceBetween(GameObject * attacker, GameObject * target)
{
	if (attacker == NULL || target == NULL)
		return 1000;
	if (attacker->GetID() == target->GetID())
		return 1000;
	auto victimPosition = attacker->GetBody().GetPos();
	auto myPosition = target->GetBody().GetPos();
	auto vecDistance = victimPosition - myPosition;
	float distance = D3DXVec3Length(&vecDistance);
	if (distance == 0.0f)
		int a = 10;
	return distance;
}

bool utility::isNear(D3DXVECTOR3 &pos, D3DXVECTOR3 &target, float nearDist)
{
	return
		(abs(pos.x - target.x) < nearDist) &&
		(abs(pos.y - target.y) < nearDist) &&
		(abs(pos.z - target.z) < nearDist);
}