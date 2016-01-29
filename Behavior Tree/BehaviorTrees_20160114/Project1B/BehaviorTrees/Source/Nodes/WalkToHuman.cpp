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
	human = utility::findTargetinRadius(me, OBJECT_Human, RADIUSTOFLEE);
	if (human != NULL && me!=NULL)
	{
		me->GetMovement().SetTarget(human->GetBody().GetPos());
		if(utility::isToNear(me->GetBody().GetPos(),human->GetBody().GetPos(),RADIUSTOIDLE))
		{
			int health = (human->GetBody().GetHealth());
			if(health <=50)
			{
				human->GetMovement().SetIdleSpeed();
				currentStatus = NS_Completed;
				me->MarkForDeletion();
				MSG_Data data;
				SendMsg(MSG_Killed, me->GetID(), me->GetID(), "DecoratorRunUntilMessage", "", data);
				/*SendMsgDelayed(1.0f, MSG_Killed, me->GetID(), me->GetID(), "DecoratorRunUntilMessage", "", data);
				SendMsgDelayed(3.0f, MSG_Killed, me->GetID(), me->GetID(), "DecoratorRunUntilMessage", "", data);
				SendMsgDelayed(5.0f, MSG_Killed, me->GetID(), me->GetID(), "DecoratorRunUntilMessage", "", data);*/
			}
			human->GetBody().SetHealth(--health);
		}
	}
	else
	{
		MSG_Data data;
		currentStatus = NS_Completed;
		//SendMsgDelayed(1.0f,MSG_Killed, me->GetID(), me->GetID(), "DecoratorRunUntilMessage", "", data);
	}

}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(WalkToHuman)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

