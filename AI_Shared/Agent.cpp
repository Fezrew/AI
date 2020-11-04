#include "Agent.h"
#include "IBehaviour.h"
#include "raymath.h"
#include <vector>

Agent::Agent(Color col, int size, Vector2 position, float speed)
{
	SetColour(col);
	SetSize(size);
	SetPosition(position);
	SetMaxSpeed(speed);
}

Agent::~Agent()
{
	for (IBehaviour* b : m_behaviourList)
	{
		// TODO: Fix
		//delete b;
	}
}

Vector2 Agent::Truncate(Vector2 v, float max)
{
	float i = max / Vector2Length(v);
	i = i < 1.0 ? i : 1.0;
	return Vector2Scale(v, i);
}

// Update the agent and its behaviours
void Agent::Update(float deltaTime)
{
	//Loop over all behaviours and Update them
	for (IBehaviour* b : m_behaviourList)
	{
		b->Update(this, deltaTime);
	}

	//Integrate the velocity to apply a position change
	Vector2 velocity = GetVelocity();
	//Apply the velocity to modifiy position
	Vector2 translation = Vector2Scale(velocity, deltaTime);
	SetPosition(Vector2Add(GetPosition(), translation));
}

//Draw the agent
void Agent::Draw()
{
	//DrawRectangle(m_position.x, m_position.y, m_size, m_size, m_colour);
	//DrawCircle(m_position.x, m_position.y, m_size, m_colour);

	//Loop over all behaviours and allow them to draw
	for (IBehaviour* b : m_behaviourList)
	{
		b->Draw(this);
	}
}

