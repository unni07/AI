#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"




LEAF_UPDATE_FUNC(ChaseHuman)
{
	GameObject * me = g_database.Find(self);
	if(currentStatus == NS_OnEnter)
	{
		human = NULL;
		currentStatus = NS_Running;
	
		human = utility::findTargetinRadius(me, OBJECT_Human, RADIUSTOFLEE +0.2 );
		if (human != NULL)
		{
			//me->GetMovement().SetJogSpeed();
			if(!human->IsMarkedForDeletion())
			me->GetMovement().SetTarget(human->GetBody().GetPos());

		}
		else
			currentStatus = NS_Failed;
	}
	
	if(currentStatus == NS_Running && human!=NULL)
	{
		me->GetMovement().SetTarget(human->GetBody().GetPos());
		currentStatus = NS_Completed;
	}
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(ChaseHuman)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

