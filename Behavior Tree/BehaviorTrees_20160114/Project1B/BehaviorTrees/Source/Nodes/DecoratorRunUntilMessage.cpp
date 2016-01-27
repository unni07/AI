#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(DecoratorRunUntilMessage)
{
	if (currentStatus == NS_OnEnter)
	{
		currentStatus = NS_Running;
		m_currentChildIndex = 0;
	}
	currentStatus = NS_Running;
	if (childStatus == NS_Failed)
		currentStatus = NS_Failed;
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(DecoratorRunUntilMessage)
{
	if(name == MSG_Killed)
	{
		currentStatus = NS_Completed;
	}
}
END_NODE_MSG_RECEIVED