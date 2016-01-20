#pragma once
#include "statemch.h"
class FeebleZombie : public StateMachine
{
public:
	FeebleZombie(GameObject & object, float range);
	~FeebleZombie();

private:
	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);
	float range; // range where zombie can attack human
				 //used to check whether any human is within the range
	 GameObject* findTargetinRadius(unsigned int o = OBJECT_Ignore_Type ,float radius = 0.2f);
	float distanceBetween();

	GameObject * attacker;
	GameObject * parent;
	D3DXVECTOR3 target;
};
