#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"




LEAF_UPDATE_FUNC(ReduceDistance)
{
	GameObject * me = g_database.Find(self);
	if(currentStatus == NS_OnEnter)
	{
		human = NULL;
		currentStatus = NS_Running;
	}
	human = utility::findTargetinRadius(me, OBJECT_Human, 1.0f);
	if (human != NULL)
	{
		if (!human->IsMarkedForDeletion())
		{
			me->GetMovement().SetTarget(human->GetBody().GetPos());
		}
		else
			currentStatus = NS_Completed;
	}
	else
		currentStatus = NS_Completed;
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(ReduceDistance)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

