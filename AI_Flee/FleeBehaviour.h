#pragma once
#include "IBehaviour.h"
class FleeBehaviour :
	public IBehaviour
{
public:
	FleeBehaviour() {};
	virtual ~FleeBehaviour() {};

	virtual void Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { m_destination = destination; }

private:
	Vector2 m_destination;
	float m_fleeRadius = 100;
};

