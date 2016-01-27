#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"




LEAF_UPDATE_FUNC(Kill)
{
	GameObject * me = g_database.Find(self);
	if(currentStatus == NS_OnEnter)
	{
		human = NULL;
		currentStatus = NS_Running;
	
		human = utility::findTargetinRadius(me, OBJECT_Human, 1.0f);
	}
	
	if(currentStatus == NS_Running && human!=NULL)
	{
		human->MarkForDeletion();
		currentStatus = NS_Completed;
		me->GetMovement().SetWalkSpeed();
	}
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(Kill)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

