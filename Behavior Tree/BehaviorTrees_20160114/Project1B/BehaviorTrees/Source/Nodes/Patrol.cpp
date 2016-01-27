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
	auto p = me->GetBody().GetPos();
	if (me->GetBody().GetPos().x >= 0.99f )
	{
		auto pos = me->GetBody().GetPos();
		D3DXVECTOR3 newPos = { 0.0f, pos.y, pos.z };
		me->GetMovement().SetTarget(newPos);
	}
	if(me->GetBody().GetPos().x <= 0.05f )
	{
		auto pos = me->GetBody().GetPos();
		D3DXVECTOR3 newPos = { 1.0f, pos.y, pos.z };
		me->GetMovement().SetTarget(newPos);
	}
	auto feeble = utility::findTargetinRadius(me, OBJECT_FeebleZombie, 0.02f);
	auto zombie = utility::findTargetinRadius(me, OBJECT_Zombie, 0.2f);
	if (feeble != NULL || zombie !=NULL)
	{
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