#pragma once
#include "IBehaviour.h"

class DebugBehaviour : IBehaviour
{
public:
	DebugBehaviour() {}
	virtual ~DebugBehaviour() {}

	void Draw(Agent* agent) override //Draw a line to indicate the speed of the agent
	{ 
		DrawLine(agent->GetPosition().x, agent->GetPosition().y, agent->GetPosition().x + agent->GetVelocity().x, agent->GetPosition().y + agent->GetVelocity().y, RED); 
	}

	virtual void Update(Agent* agent, float deltaTime) override {}
};
