#pragma once
#include "statemch.h"
class Zombie : public StateMachine
{
public:
	Zombie(GameObject & object);
	~Zombie();
private:
	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);
};

