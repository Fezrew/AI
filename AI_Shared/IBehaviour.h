#pragma once
#include "Agent.h"

class IBehaviour
{
public:
	IBehaviour() {}
	virtual ~IBehaviour() {}
	virtual void Draw(Agent* agents) {}

	virtual void Update(Agent* agent, float deltaTime) = 0;
};
