#pragma once
#include "raymath.h"

class Agent;

class ISteeringForce
{
public:
	//Empty constructers and destructors for base class
	virtual ~ISteeringForce() {}

	//Pure virtual function for executing the behaviour
	virtual Vector2 Update(Agent* agent, float deltaTime) = 0;

	//Virtual function for drawing directly from the behaviour
	virtual void Draw(Agent* agent) {}

	//All steering forces use an acceleration change this value to affect the amount
	void SetAcceleration(float acceleration) { m_SteeringAcceleration = acceleration; }

	//All steering forces have a weighting to act as a force multiplier
	void SetWeighting(float weighting) { m_Weighting = weighting; }
	float GetWeighting() const { return m_Weighting; }
	float GetAcceleration() const { return m_SteeringAcceleration; }

protected:
	float m_SteeringAcceleration = 1000, m_Weighting = 1;
};
