#include "DXUT.h"
#include "../database.h"
#include "../BehaviorTree.h"


LEAF_UPDATE_FUNC(Convert)
{
	if (currentStatus == NS_OnEnter)
	{
		currentStatus == NS_Running;
		counter = 0;
	}
	GameObject * me = g_database.Find(self);
	if(counter%2==0)
	{
		if(me != NULL)
		me->GetTiny().SetDiffuse(0.0f, 1.0f, 0.0f);
	}
	else
	{
		if (me != NULL)
		me->GetTiny().SetDiffuse(1.0f, 0.0f, 0.0f);
	}
}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Convert)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED