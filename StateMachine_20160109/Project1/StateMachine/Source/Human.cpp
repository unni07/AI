#include "DXUT.h"
#include "Human.h"
#include "movement.h"
#include "database.h"
#include "body.h"
#include "singleton.h"
#include "Zombie.h"
#include "example.h"

int Human::counter = 1000;
enum StateName
{
	STATE_FigureOut,
	STATE_Flee,
	STATE_Escape,
	STATE_InContact,
	STATE_Convert

};

enum SubstateName {		//Order doesn't matter
						//empty

	SUBSTATE_SlowDown
};

Human::Human(GameObject & object):StateMachine(object)
{
	
}


Human::~Human()
{
}

bool Human::States(State_Machine_Event event, MSG_Object* msg, int state, int substate)
{
	BeginStateMachine
		
		OnMsg(MSG_Reset)
		ResetStateMachine();

		OnMsg(MSG_MouseClick)
		m_owner->GetMovement().SetTarget(msg->GetVector3Data());

	DeclareState(STATE_FigureOut)
		OnEnter
		m_owner->GetMovement().SetWalkSpeed();
			D3DXVECTOR3 target(0, 0, 0);
			target.x = static_cast<float>(rand() % 256) / 256.f;
			target.z = static_cast<float>(rand() % 256) / 256.f;
			m_owner->GetMovement().SetTarget(target);
		OnUpdate
			auto go = findTargetinRadius();
			if(go!=NULL)
			{
				ChangeState(STATE_Flee);
				go = NULL;
			}
			OnMsg(MSG_Arrived)
				ChangeState(STATE_FigureOut);
		
	DeclareState(STATE_Flee)
		OnEnter
			m_owner->GetMovement().SetJogSpeed();
			//auto direction = m_owner->GetBody().GetDir();
			//m_owner->GetBody().SetDir(direction);
			ChangeState(STATE_Escape);
	DeclareState(STATE_Escape)
		OnEnter
		D3DXVECTOR3 target(0, 0, 0);
		auto currTarget = m_owner->GetMovement().GetTarget();
		target.x = static_cast<float>(rand() % 256) / 256.f; //+currTarget.x;
		target.z = static_cast<float>(rand() % 256) / 256.f;// +currTarget.z;
		m_owner->GetMovement().SetTarget(target);
		OnUpdate
			auto go = findTargetinRadius();
			if (go == NULL)
			{
				ChangeState(STATE_FigureOut);
			}
			else
			{
				auto distance = distanceBetween();
				if(distance <= 0.1f)
				{
					ChangeState(STATE_InContact);
				}
			}

		OnMsg(MSG_Arrived)
			auto go = findTargetinRadius();
			if (go != NULL)
			{
				ChangeState(STATE_Escape);
			}
			DeclareState(STATE_InContact)
				OnEnter
				m_owner->GetMovement().SetIdleSpeed();
				ChangeSubstate(SUBSTATE_SlowDown);
			OnUpdate
				int a = 10;
			DeclareSubstate(SUBSTATE_SlowDown)
				OnEnter
				m_owner->GetMovement().SetWalkSpeed();
				OnUpdate
				m_owner->GetMovement().SetWalkSpeed(1.0 / 8.0f);
				OnPeriodicTimeInState(2.0f)
					auto distance = distanceBetween();
					if (distance > 0.1f)
						ChangeState(STATE_Escape);
					else
						ChangeState(STATE_Convert);
			DeclareState(STATE_Convert)
				OnEnter
					m_owner->setObjectType(OBJECT_Enemy);
					/*char name[10] = "Zombie";
					sprintf(name, "%s%d", name, counter++);*/
					m_owner->setName("ConvertedZombie");
					SendMsg(MSG_CONVERTED, predator->GetID(), MSG_Data(m_owner->GetID()));
					ReplaceStateMachine(*new Zombie(*m_owner,0.1));
		EndStateMachine
}

const GameObject* Human::findTargetinRadius(float radius)
{
	dbCompositionList listHumans;
	int a = OBJECT_Enemy;
	g_database.ComposeList(listHumans, OBJECT_Enemy);
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
	predator = go;
	return go;
}

float Human::distanceBetween()
{
	if (predator == NULL)
		return 1000.0f;
	auto victimPosition = predator->GetBody().GetPos();
	auto myPosition = m_owner->GetBody().GetPos();
	auto vecDistance = victimPosition - myPosition;
	float distance = D3DXVec3Length(&vecDistance);
	return distance;
}
