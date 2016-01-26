#include "DXUT.h"
#include "../BehaviorTree.h"

LOGIC_UPDATE_FUNC(SelectorParallel)
{
	if (currentStatus == NS_OnEnter)
	{
		initialized = false;
	}

	if (!initialized)
	{
		m_currentChildIndex = 0;
		activeChildren.clear();
		childStatuses.clear();

		for (unsigned i = 0; i < m_children.size(); ++i)
		{
			activeChildren.push_back(1);
			childStatuses.push_back(NS_Running);
		}

		currentStatus = NS_Running;
		initialized = true;
	}

	int completedChildren = 0;

	for (unsigned i = 0; i < m_children.size(); ++i)
	{
		if (activeChildren[i] && childStatuses[i] == NS_Running)
		{
			childStatuses[i] = m_children[i]->Update(self, dt);

			switch (childStatuses[i])
			{
			case NS_Completed:
				activeChildren[i] = 0;
				completedChildren++;
				break;
			case NS_Failed:
				currentStatus = NS_Failed;
				goto outer;
			default:
				break;
			}
		}
		else
		{
			completedChildren++;
		}
	}

outer:
	if (completedChildren == m_children.size())
	{
		currentStatus = NS_Completed;
	}

}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(SelectorParallel)
{

}
END_NODE_MSG_RECEIVED