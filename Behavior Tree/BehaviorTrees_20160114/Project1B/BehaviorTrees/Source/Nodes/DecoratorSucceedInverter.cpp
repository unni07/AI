#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(DecoratorSucceedInverter)
{
		if (currentStatus == NS_OnEnter)
		{
			currentStatus = NS_Running;
			m_currentChildIndex = 0;
		}
		else if (childStatus == NS_Completed)
	  {
			currentStatus = NS_Failed;
		}
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(DecoratorSucceedInverter)
{

}
END_NODE_MSG_RECEIVED
