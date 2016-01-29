#include "DXUT.h"

#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"



LEAF_UPDATE_FUNC(Flee)
{
	GameObject * me = g_database.Find(self);
	if (currentStatus == NS_OnEnter)
	{
		me->GetMovement().SetJogSpeed();
		radius = 0.02f;
		currentStatus = NS_Running;
		D3DXVECTOR3 target(0, 0, 0);
		target.x = (float)(rand() % 256) / 256.f;
		target.z = (float)(rand() % 256) / 256.f;
		me->SetTargetPOS(target);
		//currentStatus = NS_Failed;
		//me->GetMovement().SetJogSpeed();
	}
	GameObject * targetZombie = utility::findTargetinRadius(me, OBJECT_Zombie, RADIUSTOFLEE);
	if(currentStatus == NS_Running && targetZombie !=NULL)
	{
		/*D3DXVECTOR3 target(0, 0, 0);
		target.x = (float)(rand() % 256) / 256.f;
		target.z = (float)(rand() % 256) / 256.f;
		me->SetTargetPOS(target);*/
		//currentStatus = NS_Failed;
	}
	if(utility::distanceBetween(me,targetZombie) <= RADIUSTOFLEE)
	{
		currentStatus = NS_Completed;
	}
	if (me != NULL && !me->IsMarkedForDeletion())
	{
		if (utility::isNear(me->GetTargetPOS(), me->GetBody().GetPos(), RADIUSTOFLEE + 0.1f))
		{
			MSG_Data data;
			SendMsg(MSG_FLEE, me->GetID(), me->GetID(), "Flee", "", data);
		}
	}
}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Flee)
{
	// Used for receiving messages
	GameObject * me = g_database.Find(self);
	if (me != NULL)
	{
		if (name == MSG_FLEE)
		{
			D3DXVECTOR3 target(0, 0, 0);
			target.x = (float)(rand() % 256) / 256.f;
			target.z = (float)(rand() % 256) / 256.f;
			me->SetTargetPOS(target);
			currentStatus = NS_Failed;
		}
	}
}
END_NODE_MSG_RECEIVED