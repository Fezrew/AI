/*#pragma once
#include "State.h"

class Agent;

// could be replaced with a vector2
struct Force 
{
	float x, y;
};

struct WanderData 
{
	float circleDistance = 80, circleRadius = 50, wanderAngle = 0, angleChange = 50;
};

// abstract class
class SteeringForce 
{
public:
	SteeringForce() {}
	virtual ~SteeringForce() {}
	// pure virtual function
	virtual Force GetForce(Agent* agent) const = 0;
};

// weighted steering force
struct WeightedForce 
{
	SteeringForce* force;
	float weight;
};

// steering behaviour
class SteeringBehaviour : public Behaviour 
{
public:
	SteeringBehaviour() {}
	virtual ~SteeringBehaviour() {}

	void AddForce(SteeringForce* force, float weight = 1.0f) 
	{
		WeightedForce wf = { force, weight };
		m_forces.push_back(wf);
	}

	void SetWeightForForce(SteeringForce* force, float weight) 
	{
		for (auto& wf : m_forces) {
			if (wf.force == force)
				wf.weight = weight;
		}
	}

	virtual eBehaviourResult Execute(Agent* agent, float deltaTime);
protected:
	std::vector<WeightedForce>	m_forces;
};

// steering behaviour state for a FSM
class SteeringState : public State 
{
public:
	SteeringState() {}
	virtual ~SteeringState() {}

	void AddForce(SteeringForce* force, float weight = 1.0f) 
	{
		WeightedForce wf = { force, weight };
		m_forces.push_back(wf);
	}

	void SetWeightForForce(SteeringForce* force, float weight) 
	{
		for (auto& wf : m_forces) 
		{
			if (wf.force == force)
				wf.weight = weight;
		}
	}

	virtual void Update(Agent* agent, float deltaTime);
protected:
	std::vector<WeightedForce>	m_forces;
};

class WanderForce : public SteeringForce 
{
public:
	WanderForce() {}
	virtual ~WanderForce() {}
	virtual Force GetForce(Agent* gameObject) const;
private:
	Vector2 SetAngle(Vector2 vector, float value) const;
};*/

#pragma once
#include "IBehaviour.h"
#include "ISteeringForce.h"

//class ISteeringForce;

class SteeringBehaviour : public IBehaviour
{
public:
	SteeringBehaviour() {}
	~SteeringBehaviour() { for (ISteeringForce* sf : m_steeringForces) { delete sf; } }
	virtual void Update(Agent* agent, float deltaTime) override;
	virtual void Draw(Agent* agent) override { for (ISteeringForce* sf : m_steeringForces) { sf->Draw(agent); } }
	void AddSteeringForce(ISteeringForce* steeringForce) { m_steeringForces.push_back(steeringForce); }
	void SetMaxAcceleration(float maxAcceleration = FLT_MAX) { m_maxAcceleration = maxAcceleration; }
	void SetMass(float mass = 1) { m_mass = mass; }
	float GetMaxAcceleration() const { return m_maxAcceleration; }
	float GetMass() const { return m_mass; }
protected:
	vector<ISteeringForce*> m_steeringForces;
	float m_maxAcceleration = FLT_MAX, m_mass = 1;
private:
	Vector2 Truncate(Vector2 c, float max);
};
