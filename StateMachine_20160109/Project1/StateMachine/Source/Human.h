#pragma once
#include "statemch.h"
class GameObject;

class Human: public StateMachine
{
public:
	Human(GameObject & object);
	~Human();
private:
	virtual bool States(State_Machine_Event event, MSG_Object * msg, int state, int substate);
	static int counter;

	const GameObject* findTargetinRadius(float radius = 0.2);
	float distanceBetween();
	GameObject * predator;
};

