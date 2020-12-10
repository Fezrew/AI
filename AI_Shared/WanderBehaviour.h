#pragma once
#include "IBehaviour.h"

class WanderBehaviour :
	public IBehaviour
{
public:
	WanderBehaviour();
	virtual ~WanderBehaviour() {};

	virtual void Update(Agent* agent, float deltaTime);

	void Draw(Agent* agent);	// for debug only

private:
	Vector2 SetAngle(Vector2 vector, float value);

	float m_circleDistance = 60;
	float m_circleRadius = 50;
	float m_wanderAngle = 0;

	const float m_angleChange = 50;

	/// DEBUG ONLY
	Vector2 debug_cirleCenter;
	Vector2 debug_displacement;
	/// DEBUG ONLY
};

