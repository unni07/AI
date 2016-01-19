
#include "DXUT.h"
#include "Zombie.h"
#include "movement.h"

enum StateName{
	STATE_Wander,
	STATE_Chase,
	STATE_Convert,
	STATE_Flee,
	STATE_Idle
};

Zombie::Zombie(GameObject & object) : StateMachine(object)
{

}


Zombie::~Zombie()
{
}

bool Zombie::States(State_Machine_Event event, MSG_Object * msg, int state, int substate)
{
	BeginStateMachine

		OnMsg(MSG_Reset)
			ResetStateMachine();

		OnMsg(MSG_MouseClick)
			m_owner->GetMovement().SetTarget(msg->GetVector3Data());

		DeclareState(STATE_Wander)
			OnEnter
				m_owner->GetMovement().SetIdleSpeed();
				ChangeStateDelayed(1.0f, STATE_Chase);
			DeclareState(STATE_Chase)
				m_owner->GetMovement().SetJogSpeed();
			DeclareState(STATE_Convert)

			DeclareState(STATE_Flee)

			DeclareState(STATE_Idle)
	


	EndStateMachine
}