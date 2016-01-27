#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"




LEAF_UPDATE_FUNC(WalkToHuman)
{
	GameObject * me = g_database.Find(self);
	if(currentStatus == NS_OnEnter)
	{
		human = NULL;
		currentStatus = NS_Running;
		me->GetMovement().SetWalkSpeed();
		
	}
	human = utility::findTargetinRadius(me, OBJECT_Human, 1.0f);
	if (human != NULL)
	{
		me->GetMovement().SetTarget(human->GetBody().GetPos());
	}
	else
		currentStatus = NS_Failed;
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(WalkToHuman)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

