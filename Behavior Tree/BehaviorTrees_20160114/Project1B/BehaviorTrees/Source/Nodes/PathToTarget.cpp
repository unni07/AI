#include "DXUT.h"
#include "../gameobject.h"
#include "../BehaviorTree.h"
#include "../database.h"
#include "../body.h"
#include "../movement.h"

bool isNear(D3DXVECTOR3 &pos, D3DXVECTOR3 &target, float nearDist = 1.f / 100.f)
{
  return
    (abs(pos.x - target.x) < nearDist) &&
    (abs(pos.y - target.y) < nearDist) &&
    (abs(pos.z - target.z) < nearDist);
}

LEAF_UPDATE_FUNC(PathToTarget)
{
  GameObject *me = g_database.Find(self);
  if (me)
  {
    if (currentStatus == NS_OnEnter)
    {
      me->GetMovement().SetWalkSpeed();
      me->GetMovement().SetTarget(me->GetTargetPOS());
      currentStatus = NS_Running;
    }
    else
    {
      if (isNear(me->GetBody().GetPos(), me->GetTargetPOS()))
      {
        currentStatus = NS_Completed;
        me->GetMovement().SetIdleSpeed();
      }
    }
  }
  else
  {
    currentStatus = NS_Failed;
  }
}
END_LEAF_UPDATE_FUNC

NODE_MSG_RECEIVED(PathToTarget)
{
	GameObject *me = g_database.Find(self);
	if (name == MSG_Arrived)
	{
		currentStatus = NS_Completed;
		me->GetMovement().SetIdleSpeed();

	}
}
END_NODE_MSG_RECEIVED