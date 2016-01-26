#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(DecoratorRunUntilFail)
{
	if (currentStatus == NS_OnEnter)
	{
		m_currentChildIndex = 0;
		currentStatus = NS_Running;
	}
	else
	{
		if (childStatus == NS_Failed)
		{
			currentStatus = NS_Completed;
		}
	}
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(DecoratorRunUntilFail)
{

}
END_NODE_MSG_RECEIVED