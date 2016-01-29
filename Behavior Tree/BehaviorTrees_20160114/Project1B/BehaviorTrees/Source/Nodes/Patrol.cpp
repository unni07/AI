#include "DXUT.h"
#include "../database.h"
#include "../BehaviorTree.h"
#include "../body.h"
#include"../movement.h"

LEAF_UPDATE_FUNC(Patrol)
{
	GameObject * me = g_database.Find(self);
	if (currentStatus == NS_OnEnter)
	{
		currentStatus = NS_Running;

	}
	if (me != NULL)
	{
		if (me->GetBody().GetPos().x >= 0.99f)
		{
			auto pos = me->GetBody().GetPos();
			D3DXVECTOR3 newPos = { 0.0f, pos.y, pos.z };
			me->GetMovement().SetTarget(newPos);
		}
		if (me->GetBody().GetPos().x <= 0.05f)
		{
			auto pos = me->GetBody().GetPos();
			D3DXVECTOR3 newPos = { 1.0f, pos.y, pos.z };
			me->GetMovement().SetTarget(newPos);
		}
	}
	auto feeble = utility::findTargetinRadius(me, OBJECT_FeebleZombie, RADIUSTOFLEE);
	auto zombie = utility::findTargetinRadius(me, OBJECT_Zombie, RADIUSTOFLEE);
	if (feeble != NULL || zombie !=NULL)
	{
	
		if(zombie!=NULL && currentStatus==NS_Running)
		{
			MSG_Data data;
			//SendMsgDelayed(1.0f,MSG_FLEE, me->GetID(), me->GetID(), "Flee", "",data);
		}
		currentStatus = NS_Failed;
	}
	else
		currentStatus = NS_Completed;

}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Patrol)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED