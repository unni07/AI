#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(SequenceRandomly)
{
	if (currentStatus == NS_OnEnter)
	{
		initialized = false;
		srand(0.0f);
		m_currentChildIndex = rand() % m_children.size();
	}
	if(!initialized)
	{
		childStatuses.clear();

		for (unsigned i = 0; i < m_children.size(); ++i)
		{
			childStatuses.push_back(NS_Running);
		}

		currentStatus = NS_Running;
		initialized = true;
	}
	int completedChildren = 0;
	m_currentChildIndex = rand() % m_children.size();
	for (unsigned int i = 0; i < m_children.size();++i)
	{
		childStatuses[i] = m_children[i]->Update(self, dt);
		if(childStatuses[i] == NS_Completed)
		{
			completedChildren++;
		}
	}
	if (completedChildren == m_children.size())
	{
		currentStatus = NS_Completed;
	}
	else
		currentStatus = NS_Failed;
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(SequenceRandomly)
{

}
END_NODE_MSG_RECEIVED