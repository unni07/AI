
#include "DXUT.h"
#include "Zombie.h"
#include "movement.h"
#include "database.h"
#include "body.h"
enum StateName{

	STATE_Idle,
	STATE_Wander,
	STATE_Chase,
	STATE_Convert,
	
};

enum SubstateName
{
	SUBSTATE_ChangeColor,
	SUBSTATE_ChangeColorGreen

};
Zombie::Zombie(GameObject & object, float range_) : StateMachine(object), range(range_), victim(NULL)
{
}


Zombie::~Zombie()
{
}
int counter = 0;
bool Zombie::States(State_Machine_Event event, MSG_Object * msg, int state, int substate)
{
	counter++;
	if (counter >= INT_MAX)
		counter = 0;
	BeginStateMachine

		OnMsg(MSG_Reset)
			ResetStateMachine();

		OnMsg(MSG_MouseClick)
			//m_owner->GetMovement().SetTarget(msg->GetVector3Data());

		DeclareState(STATE_Idle)
			OnEnter
				m_owner->GetMovement().SetIdleSpeed();
		OnUpdate
				const GameObject * go = findTargetinRadius();
				if(go!=NULL)
					{
						ChangeState(STATE_Chase);
						BroadcastAddToList(m_owner->GetID());
					}
		DeclareState(STATE_Chase)
					OnEnter
					
			if (!victim->IsMarkedForDeletion() || victim!=NULL)
			{
				m_owner->GetMovement().SetWalkSpeed();
				m_owner->GetMovement().SetTarget(victim->GetBody().GetPos());
			}
		OnPeriodicTimeInState(1.0f)
					if(!victim->IsMarkedForDeletion() || victim!=NULL)
					{
						m_owner->GetMovement().SetTarget(victim->GetBody().GetPos());
						float distance = distanceBetween();
						if (distance < 0.1)
						{
							ChangeState(STATE_Convert);
						}
					}
		DeclareState(STATE_Convert)
			OnMsg(MSG_CONVERTED)
			if(victim->GetID() == msg->GetMsgData().GetObjectID())
			{
				ChangeState(STATE_Wander);
			}
			OnEnter
			ChangeSubstate(SUBSTATE_ChangeColor);
		DeclareSubstate(SUBSTATE_ChangeColor)
				OnPeriodicTimeInState(0.2f)
				if(counter % 2==0)
				victim->GetTiny().SetDiffuse(0.0f, 1.0f, 0.0f);
				else
				victim->GetTiny().SetDiffuse(1.0f, 0.0f, 0.0f);
	
				//if (victim->GetType() == OBJECT_Enemy)
			OnMsg(MSG_CONVERTED)
				if (msg->GetMsgData().GetObjectID() == victim->GetID())
				{
					victim->GetTiny().SetDiffuse(0.0f, 1.0f, 0.0f);
					ChangeState(STATE_Wander);
				}
			
		DeclareState(STATE_Wander)
			OnEnter
			m_owner->GetMovement().SetWalkSpeed();
			D3DXVECTOR3 target(0, 0, 0);
			target.x = (float)(rand() % 256) / 256.f;
			target.z = (float)(rand() % 256) / 256.f;
			this->target = target;
			m_owner->GetMovement().SetTarget(target);
			OnUpdate
				
			OnMsg(MSG_Arrived)
				ChangeState(STATE_Idle);

	EndStateMachine
}

const GameObject* Zombie::findTargetinRadius() 
{
	dbCompositionList listHumans;
	g_database.ComposeList(listHumans, OBJECT_NPC);
	dbCompositionList::iterator iter,iterEnd;
	iter = listHumans.begin();
	iterEnd = listHumans.end();
	float distance = 100000.0f;
	GameObject *go = NULL;
	while (iter != iterEnd && distance > range)
	{
		D3DXVECTOR3 humanPosition = (*iter)->GetBody().GetPos();
		auto myPosition = m_owner->GetBody().GetPos();
		auto vecDistance = humanPosition - myPosition;
		distance = D3DXVec3Length(&vecDistance);

		if(distance<range)
		go = *iter;

		iter++;
	}
	victim = go;
	return go;
}

float Zombie::distanceBetween()
{
	if (victim->IsMarkedForDeletion())
		return 1000.0f;

	auto victimPosition = victim->GetBody().GetPos();
	auto myPosition = m_owner->GetBody().GetPos();
	auto vecDistance = victimPosition - myPosition;
	float distance = D3DXVec3Length(&vecDistance);
	return distance;
}
