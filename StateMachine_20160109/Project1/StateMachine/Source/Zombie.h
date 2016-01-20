#pragma once
#include "statemch.h"
class Zombie : public StateMachine
{
public:
	Zombie(GameObject & object, float range);
	~Zombie();

private:
	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);
	float range; // range where zombie can attack human
	//used to check whether any human is within the range
	const GameObject* findTargetinRadius();
	float distanceBetween();

	GameObject * victim;
	D3DXVECTOR3 target;
};

