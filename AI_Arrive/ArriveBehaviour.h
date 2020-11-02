#pragma once
#include "IBehaviour.h"
class ArriveBehaviour :
	public IBehaviour
{
public:
	ArriveBehaviour() {};
	virtual ~ArriveBehaviour() {};

	virtual void Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { m_destination = destination; }

private:
	Vector2 m_destination;
	float m_slowingRadius = 100;
};

