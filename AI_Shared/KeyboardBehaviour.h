#pragma once
#include "IBehaviour.h"

class KeyboardBehaviour : public IBehaviour
{
public:
	KeyboardBehaviour() {}//float speed) : m_speed{speed} {}
	virtual ~KeyboardBehaviour() {}

	virtual void Update(Agent* agent, float deltaTime);
	//void SetSpeed(float speed) { m_speed = speed; }
	//float GetSpeed() const { return m_speed; }

private:
	float m_speedIncrement = 50.0f;
	/*virtual void UpdateSpeed(Agent* agent, float& X, float& Y, float& Accel, float& Decel);*/
};
