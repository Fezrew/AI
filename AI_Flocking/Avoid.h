#ifndef AVOID_H
#define AVOID_H
#include "Behaviour.h"
#include <vector>
#include <raylib.h>

class Circle;

class Avoid : public Behaviour
{
public:
	Avoid();
	~Avoid();

	void Update(float deltaTime, Agent& agent);
	inline virtual const char* GetBehaviourName() { return "Avoid"; }

	float m_maxSeeAhead;
	float m_maxAvoidForce;

	Vector2* m_targetPosition;
	Vector2 m_aheadPosition;
	Vector2 m_aheadPosition2;
		
	std::vector<Circle*>* m_circles;
};

#endif