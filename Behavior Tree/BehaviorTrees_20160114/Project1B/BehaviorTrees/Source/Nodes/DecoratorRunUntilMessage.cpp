#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(DecoratorRunUntilMessage)
{
	if (currentStatus == NS_OnEnter)
	{
		status = false;
		currentStatus = NS_Running;
		m_currentChildIndex = 0;
	}
	currentStatus = NS_Running;
	if(status == true)
	{
		currentStatus = NS_Completed;
	}
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(DecoratorRunUntilMessage)
{
	if(name == MSG_Killed)
	{
		status = true;
	}
}
END_NODE_MSG_RECEIVED