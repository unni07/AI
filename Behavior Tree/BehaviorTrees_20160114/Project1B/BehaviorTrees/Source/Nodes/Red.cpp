#include "DXUT.h"

#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"



LEAF_UPDATE_FUNC(Red)
{
	GameObject * me = g_database.Find(self);
	if (currentStatus == NS_OnEnter)
	{
		currentStatus = NS_Running;
		
	}
	if(currentStatus == NS_Running)
	{
		me->GetTiny().SetDiffuse(1.0f, 0.0f, 0.0f);
		currentStatus = NS_Completed;
	}
}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Red)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED