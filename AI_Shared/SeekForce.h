/*#pragma once
#include "Behaviour.h"

class SeekBehaviour : public Behaviour
{
public:
	SeekBehaviour() {}
	virtual ~SeekBehaviour() {}
	virtual bool Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { m_destination = destination; }
private:
	Vector2 m_destination;
};*/

#pragma once
#include "ISteeringForce.h"

///A seek behaviour that seeks towards a destination
class SeekForce : public ISteeringForce
{
public:
	SeekForce() : m_Target({ 0, 0 }) {}
	virtual ~SeekForce() {}

	virtual Vector2 Update(Agent* agent, float deltaTime) override;

	void Draw(Agent* agent) override 
	{ 
		DrawCircle((int)m_Target.x, (int)m_Target.y, (float)agent->GetSize(), BLUE); 
	}

	void SetTarget(Vector2 target) 
	{ 
		m_Target = target; 
	}

protected:
	Vector2 m_Target;
};
