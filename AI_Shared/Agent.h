#pragma once
#include "raymath.h"
#include <vector>

using namespace std;

class IBehaviour;

class Agent
{
public:
	Agent(Color col = RED, int size = 10, Vector2 position = { 200, 150 }, float speed = 100);

	virtual ~Agent();

	//Update the agent and its behaviours
	virtual void Update(float deltaTime);

	//Draw the agent
	virtual void Draw();

	//Add a behaviour to the agent
	void AddBehaviour(IBehaviour* behaviour) { m_behaviourList.push_back(behaviour); }

	//Movement functions
	void SetVelocity(Vector2 velocity) { m_velocity = velocity; }
	void SetPosition(Vector2 position) { m_position = position; }
	void SetSpeed(Vector2 speed) { m_maxSpeed = speed; }
	void SetSize(const int size) { m_size = size; }
	void SetColour(Color col) { m_colour = col; }

	int GetSize() const { return m_size; }
	Vector2 GetSpeed() { return m_maxSpeed; }
	Vector2 GetPosition() { return m_position; }
	Vector2 GetVelocity() { return m_velocity; }
	Color GetColour() const { return m_colour; }

	void AddForce(Vector2 force) { m_force = Vector2Add(force, m_force); }

protected:
	vector<IBehaviour*> m_behaviourList;
	Vector2 m_position;
	Vector2 m_velocity; 
	Vector2 m_force = { 0, 0 };
	float m_maxSpeed;

	int m_size;
	Color m_colour;

	//Keep between 0 and 1, 0 is max friction, 1 is no friction
	float m_frictionModifier = 0.99;

private:
	Vector2 Truncate(Vector2 v, float max);
};
