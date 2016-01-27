#include "DXUT.h"

#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"



LEAF_UPDATE_FUNC(Green)
{
	GameObject * me = g_database.Find(self);
	if (currentStatus == NS_OnEnter)
	{
		currentStatus = NS_Running;
		counter = 0;
	}
	counter++;
	if(currentStatus == NS_Running && counter%8==0)
	{
		me->GetTiny().SetDiffuse(0.0f, 1.0f, 0.0f);
		currentStatus = NS_Completed;
	}
}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Green)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED