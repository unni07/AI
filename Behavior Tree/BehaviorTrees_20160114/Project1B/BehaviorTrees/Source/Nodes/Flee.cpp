#include "DXUT.h"

#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"




LEAF_UPDATE_FUNC(Flee)
{
	GameObject * me = g_database.Find(self);
	if (currentStatus == NS_OnEnter)
	{
		radius = 0.02f;
		currentStatus == NS_Running;
	}
	GameObject * target = utility::findTargetinRadius(me, OBJECT_Zombie, 0.2f);
	if(target)
	{
		D3DXVECTOR3 target(0, 0, 0);
		target.x = (float)(rand() % 256) / 256.f;
		target.z = (float)(rand() % 256) / 256.f;
		me->SetTargetPOS(target);
		currentStatus = NS_Completed;
	}
}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Flee)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED