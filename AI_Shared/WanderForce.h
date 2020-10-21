#pragma once
#include "Agent.h"
#include "ISteeringForce.h"

class WanderForce : public ISteeringForce
{
public:
	WanderForce() {}
	virtual ~WanderForce() {};
	virtual Vector2 Update(Agent* agent, float deltaTime) override;
	void Draw(Agent* agent) override;
	void SetWanderDestination(float dist) { m_wanderDistance = dist; }
	void SetWanderRadius(float radius) { m_wanderRadius = radius; }
	float GetWanderDistance() const { return m_wanderDistance; }
	float GetWanderRadius() const { return m_wanderRadius; }
#if USE_WANDER_DESTINATION
	void SetCloseEnoughDistance(float dist) { m_CloseEnoughDistance = dist; }
	float GetCloseEnoughDistance() const { return m_CloseEnoughDistance; }
#endif
private:
#if USE_WANDER_DESTINATION
	Vector2 calculateNewWanderDestination(Agent* agent);
#else
	Vector2 SetAngle(Vector2 vector, float value);
#endif
	float m_wanderDistance = 0, m_wanderRadius = 250;
#if USE_WANDER_DESTINATION
	float m_CloseEnoughDistance = 5;
	int m_margin = 15;
	bool m_calculateNewTarget = true;
	Vector2 m_WanderDestination;
#endif
};
