#include "DXUT.h"
#include "../BehaviorTree.h"
#include "../database.h"
LOGIC_UPDATE_FUNC(DecoratorRunXTimes)
{
	if (currentStatus == NS_OnEnter)
	{
		currentStatus = NS_Running;
		m_currentChildIndex = 0;
		x = 100;
	}
	else
	{
		if (x-- <= 0)
		{
			currentStatus = NS_Completed;
		}
		else
			currentStatus = NS_Running;
		if(currentStatus == NS_Completed)
		{
			GameObject * me = g_database.Find(self);
			//me->setType(OBJECT_Zombie);
		}
	}
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(DecoratorRunXTimes)
{

}
END_NODE_MSG_RECEIVED