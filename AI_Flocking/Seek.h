#ifndef SEEK_H
#define SEEK_H

//--------
//	Brief: A Seek Behaviour for an agent
//	Author: Elizabeth Rowlands
//	Date: 4/3/2015
//--------

#include "IBehaviour.h"
#include <raylib.h>

class Seek : public IBehaviour
{
public:
	Seek();
	virtual ~Seek();
	virtual void Update(Agent* agent, float deltaTime);
	inline virtual const char* GetBehaviourName() { return "Seek"; }

	// X and Y position to seek towards
	Vector2* m_targetPosition;
};

#endif