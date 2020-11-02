#ifndef ARRIVE_H
#define ARRIVE_H

//--------
//	Brief: An Arrive Behaviour for an agent
//	Author: Elizabeth Rowlands
//	Date: 4/3/2015
//--------

#include "Behaviour.h"
#include <raylib.h>

class Arrive : public Behaviour
{
public:
	Arrive();
	virtual ~Arrive();
	virtual void Update(float deltaTime, Agent& agent);
	inline virtual const char* GetBehaviourName() { return "Arrive"; }

	Vector2* m_targetPosition;
	float m_distance;
};

#endif