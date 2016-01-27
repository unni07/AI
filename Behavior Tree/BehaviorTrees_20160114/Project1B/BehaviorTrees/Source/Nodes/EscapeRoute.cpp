#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"


LEAF_UPDATE_FUNC(EscapeRoute)
{
  GameObject *me = g_database.Find(self);
  GameObject * targetZombie = utility::findTargetinRadius(me, OBJECT_Zombie, 1.0f);
  if (me)
  {
    if (currentStatus == NS_OnEnter)
    {
     // me->GetMovement().SetWalkSpeed();
      me->GetMovement().SetTarget(me->GetTargetPOS());
      currentStatus = NS_Running;
    }
    else
    {
		auto f = utility::distanceBetween(me, targetZombie);
      if (utility::distanceBetween(me, targetZombie) <=0.01f)
      {
        currentStatus = NS_Completed;
        me->GetMovement().SetIdleSpeed();
      }
	  else
		  currentStatus = NS_Failed;
    }
  }
  else
  {
    currentStatus = NS_Failed;
  }
  
  if (utility::isNear(me->GetBody().GetPos(), me->GetTargetPOS()))
  {

	  D3DXVECTOR3 target(0, 0, 0);
	  target.x = (float)(rand() % 256) / 256.f;
	  target.z = (float)(rand() % 256) / 256.f;
	  me->SetTargetPOS(target);


	  MSG_Data data;
	  SendMsg(MSG_FLEE, me->GetID(), me->GetID(), "Flee", "", data);
  }
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(EscapeRoute)
{
	GameObject *me = g_database.Find(self);
	if (name == MSG_Arrived)
	{
		currentStatus = NS_Completed;
		me->GetMovement().SetIdleSpeed();

	}
}
END_NODE_MSG_RECEIVED