#ifndef PURSUE_H
#define PURSUE_H
#include "Behaviour.h"
#include <raylib.h>

class Pursue :	public Behaviour
{
public:
	Pursue();
	~Pursue();
	void Update(float deltaTime, Agent& agent);
	inline virtual const char* GetBehaviourName() { return "Pursue"; }

	Vector2* m_targetPosition;
	Vector2* m_targetVelocity;
};

#endif