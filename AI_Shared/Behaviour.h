#pragma once
#include "Agent.h"

class Behaviour
{
public:
	//Empty constructors and destructors for base class
	Behaviour() {}
	virtual ~Behaviour() {}
	//Pure virtual function for executing the behaviour
	virtual void Update(Agent* agent, float deltaTime) = 0;
};
