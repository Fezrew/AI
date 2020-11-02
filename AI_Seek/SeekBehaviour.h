#pragma once
#include "IBehaviour.h"
class SeekBehaviour :
	public IBehaviour
{
public:
	SeekBehaviour() {};
	virtual ~SeekBehaviour() {};

	virtual void Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { m_destination = destination; }

private:
	Vector2 m_destination;
};

