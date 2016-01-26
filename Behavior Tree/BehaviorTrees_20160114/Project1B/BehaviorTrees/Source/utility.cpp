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


