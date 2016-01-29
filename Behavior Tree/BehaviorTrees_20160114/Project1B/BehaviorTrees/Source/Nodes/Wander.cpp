#include "DXUT.h"
#include "../database.h"
#include "../BehaviorTree.h"
#include "../body.h"
#include"../movement.h"

LEAF_UPDATE_FUNC(Wander)
{
	GameObject * me = g_database.Find(self);
	if (currentStatus == NS_OnEnter)
	{
		currentStatus = NS_Running;
		x = 100;
		accumulator = dt;
	}
	 if (currentStatus == NS_Running|| currentStatus == NS_Failed)
	{
		//srand(dt);
		D3DXVECTOR3 target(0, 0, 0);
		target.x = (float)(rand() % 256) / 256.f ;
		target.z = (float)(rand() % 256) / 256.f ;
		//me->SetTargetPOS(target);
		me->GetMovement().SetTarget(target);
		currentStatus = NS_Temp;
	}
	 if(accumulator++ > x)
	 {
		 currentStatus = NS_Running;
		 accumulator = dt;
		 currentStatus = NS_Failed;
		
	 }
	 if (me != NULL)
	 {
		 auto f = utility::isToNear(me->GetBody().GetPos(), me->GetTargetPOS());
		 if (utility::isToNear(me->GetBody().GetPos(), me->GetTargetPOS(), 0.1f) <= 0.1f || f > 0.6f)
		 {
			 //currentStatus = NS_Running;
		 }
	 }
}
END_LEAF_UPDATE_FUNC


NODE_MSG_RECEIVED(Wander)
{
	// Used for receiving messages
}
END_NODE_MSG_RECEIVED