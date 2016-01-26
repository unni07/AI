#include "DXUT.h"
#include "../BehaviorTree.h"
LOGIC_UPDATE_FUNC(SelectorInOrder)
{
  if (currentStatus == NS_OnEnter)
  {
    currentStatus = NS_Running;
    m_currentChildIndex = 0;
  }
  else
  {
    if (childStatus == NS_Failed)
    {
      m_currentChildIndex++;

      if (m_currentChildIndex >= (int)m_children.size())
      {
        currentStatus = NS_Failed;
      }
    }
    else if (childStatus == NS_Completed)
    {
      currentStatus = NS_Completed;
    }
  }
}
END_LOGIC_UPDATE_FUNC

NODE_MSG_RECEIVED(SelectorInOrder)
{

}
END_NODE_MSG_RECEIVED