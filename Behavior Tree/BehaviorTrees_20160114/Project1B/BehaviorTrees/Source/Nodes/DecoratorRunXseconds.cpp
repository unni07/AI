#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(DecoratorRunXseconds)
{
		if (currentStatus == NS_OnEnter)
		{
			currentStatus = NS_Running;
			accumulator = dt;
			x = 500.0f;
			m_currentChildIndex = 0;
			
		}
//		if(childStatus == NS_Running)
		//if (currentStatus == NS_Running)
		{
			accumulator++;
			if (accumulator >= x)
			{
				currentStatus = NS_Completed;
			}
			else
				currentStatus = NS_Running;
		}
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(DecoratorRunXseconds)
{

}
END_NODE_MSG_RECEIVED