#ifndef FLEE_H
#define FLEE_H

//--------
//	Brief: A Flee Behaviour for an agent
//	Author: Elizabeth Rowlands
//	Date: 4/3/2015
//--------

#include "Behaviour.h"
#include <raylib.h>

class Flee : public Behaviour
{
public:
	Flee();
	virtual ~Flee();
	virtual void Update(float deltaTime, Agent& agent);
	inline virtual const char* GetBehaviourName() { return "Flee"; }

	// X and Y position to flee from
	Vector2 *m_targetPosition;
};

#endif