#include "DXUT.h"
#include "FeebleZombie.h"

#include "movement.h"
#include "database.h"
#include "body.h"


FeebleZombie::FeebleZombie(GameObject & object, float range): StateMachine(object)
{

}


FeebleZombie::~FeebleZombie()
{
}

enum StateName
{
	STATE_Idle,
	STATE_TakeCover,
	STATE_RunAway,
	STATE_Follow
};
bool FeebleZombie::States(State_Machine_Event event, MSG_Object* msg, int state, int substate)
{
	BeginStateMachine
		OnMsg(MSG_DEAD)
		if (!m_owner->IsMarkedForDeletion())
		{
			parent = findTargetinRadius(OBJECT_Enemy, 1.0);
			if (parent != NULL) {
				m_owner->GetMovement().SetTarget(parent->GetBody().GetPos());
				ChangeState(STATE_TakeCover);
			}
		}
		
		DeclareState(STATE_Idle)
		OnEnter
		BroadcastAddToList(m_owner->GetID());
		m_owner->GetMovement().SetIdleSpeed();
		OnUpdate
		const	GameObject * go = findTargetinRadius(OBJECT_NPC,0.2f);
		if (go != NULL)
			ChangeState(STATE_RunAway);
		DeclareState(STATE_RunAway)
			OnEnter
			m_owner->GetMovement().SetJogSpeed(1.0f/6.0f);
		OnUpdate
			auto distance = distanceBetween();
			if(distance<=0.1f)
			{
				m_owner->MarkForDeletion();
				SendMsgBroadcastNow(MSG_DEAD, m_owner->GetType(),MSG_Data(m_owner->GetID()));
				ChangeState(STATE_TakeCover);
			}
		DeclareState(STATE_TakeCover)
			OnEnter
				parent = findTargetinRadius(OBJECT_Enemy, 0.5);
		m_owner->GetMovement().SetJogSpeed();
		if(parent!=NULL)
				 m_owner->GetMovement().SetTarget(parent->GetBody().GetPos());
			OnUpdate
					 if(parent!=NULL)
						 m_owner->GetMovement().SetTarget(parent->GetBody().GetPos());
			OnMsg(MSG_Arrived)
				m_owner->GetMovement().SetIdleSpeed();
			ChangeState(STATE_Follow);
			DeclareState(STATE_Follow)
				OnUpdate
				parent = findTargetinRadius(OBJECT_Enemy, 0.5);
				if(parent!=NULL)
				{
					m_owner->GetMovement().SetWalkSpeed(1.0f/6.0f);
					m_owner->GetMovement().SetTarget(parent->GetBody().GetPos());
				}
				OnMsg(MSG_Arrived)
					m_owner->GetMovement().SetIdleSpeed();


	EndStateMachine
}


float FeebleZombie::distanceBetween()
{
	if (attacker == NULL)
		return 1000.0f;
	auto victimPosition = attacker->GetBody().GetPos();
	auto myPosition = m_owner->GetBody().GetPos();
	auto vecDistance = victimPosition - myPosition;
	float distance = D3DXVec3Length(&vecDistance);
	return distance;
}

 GameObject* FeebleZombie::findTargetinRadius(unsigned int o ,float radius)
{
	dbCompositionList listHumans;
	g_database.ComposeList(listHumans, o);
	dbCompositionList::iterator iter, iterEnd;
	iter = listHumans.begin();
	iterEnd = listHumans.end();
	float distance = 100000.0f;
	GameObject *go = NULL;
	while (iter != iterEnd && distance > radius)
	{
		D3DXVECTOR3 humanPosition = (*iter)->GetBody().GetPos();
		auto myPosition = m_owner->GetBody().GetPos();
		auto vecDistance = humanPosition - myPosition;
		distance = D3DXVec3Length(&vecDistance);

		if (distance< radius)
			go = *iter;

		iter++;
	}
	attacker = go;
	return go;
}
