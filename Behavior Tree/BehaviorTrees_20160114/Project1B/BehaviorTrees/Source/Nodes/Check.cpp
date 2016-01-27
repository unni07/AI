#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"




LEAF_UPDATE_FUNC(Check)
{
	GameObject * me = g_database.Find(self);
	if(currentStatus == NS_OnEnter)
	{
		human = NULL;
		currentStatus = NS_Running;
		initialize = false;
	
		human = utility::findTargetinRadius(me, OBJECT_Human, 1.0f);
		if (human != NULL)
		{
			me->GetMovement().SetJogSpeed();
			me->GetMovement().SetTarget(human->GetBody().GetPos());
			currentStatus = NS_Completed;
		}
		else
			currentStatus = NS_Failed;
	}
	if(!initialize)
	{
		
	}
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(Check)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

