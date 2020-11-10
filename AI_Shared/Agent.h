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
	Vector2 GetVelocity() { return m_velocity; }

	void SetPosition(Vector2 position) { m_position = position; }
	Vector2 GetPosition() { return m_position; }
	
	void SetMaxSpeed(float speed) { m_maxSpeed = speed; }
	float GetMaxSpeed() { return m_maxSpeed; }
	
	void SetSize(const int size) { m_size = size; }
	int GetSize() const { return m_size; }
	
	void SetColour(Color col) { m_colour = col; }
	Color GetColour() const { return m_colour; }

	float GetRotation() { return m_rotation; }

	Vector2 GetForce() { return m_force; }
	void AddForce(Vector2 force) { m_force = Truncate(Vector2Add(force, m_force), m_maxSpeed); }

protected:
	vector<IBehaviour*> m_behaviourList;
	Vector2 m_position;
	Vector2 m_velocity; 
	Vector2 m_force = { 0, 0 };
	float m_maxSpeed;
	float m_rotation;

	int m_size;
	Color m_colour;

	//Keep between 0 and 1, 0 is max friction, 1 is no friction
	float m_frictionModifier = 0.99;

private:
	Vector2 Truncate(Vector2 v, float max);
};
