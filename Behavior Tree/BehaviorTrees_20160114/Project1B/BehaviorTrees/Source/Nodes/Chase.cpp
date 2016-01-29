#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"




LEAF_UPDATE_FUNC(Chase)
{
	GameObject * me = g_database.Find(self);
	if(currentStatus == NS_OnEnter)
	{
		feebleZombie = NULL;
		currentStatus = NS_Running;
	
		feebleZombie = utility::findTargetinRadius(me, OBJECT_FeebleZombie, RADIUSTOFLEE);
		if (feebleZombie != NULL && !feebleZombie->IsMarkedForDeletion())
		{
			me->GetMovement().SetJogSpeed();
			me->GetMovement().SetTarget(feebleZombie->GetBody().GetPos());
		}
		else
			currentStatus = NS_Failed;
	}
	feebleZombie = utility::findTargetinRadius(me, OBJECT_FeebleZombie, RADIUSTOFLEE);
	if(currentStatus != NS_Completed && feebleZombie!=NULL && me!=NULL)
	{
		if(!feebleZombie->IsMarkedForDeletion())
		{
			auto body = me->GetBody();
			auto m = feebleZombie->GetBody();
			if(m.IsAlive())
			me->GetMovement().SetTarget(feebleZombie->GetBody().GetPos());
		}
	}
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(Chase)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED

