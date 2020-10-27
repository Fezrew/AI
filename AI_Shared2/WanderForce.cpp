#include <iostream>
#include "WanderForce.h"

Vector2 WanderForce::SetAngle(Vector2 vector, float value)
{
	float length = Vector2Length(vector);
	return { cosf(value) * length, sinf(value) * length };
}

Vector2 WanderForce::Update(Agent* agent, float deltaTime)
{
	Vector2 velocity = agent->GetVelocity();
	if (Vector2Length(velocity) == 0)
	{
		velocity = { 0, -1 };
	}
	//New implementation
#if USE_WANDER_DESTINATION
#if 1
	Vector2 wanderForce = { 0, 0 };

	//Calculate new wander target?
	if (m_calculateNewTarget)
	{
		//The code to calulate the circle center:
		//m_circleDistance from the current agent position, in the same direction as the current velocity
		Vector2 wanderDistance = Vector2Scale(Vector2Normalize(velocity), m_circleDistance);
		Vector2 circleCenter = Vector2Add(agent->GetPosition(), wanderDistance);
		//Add a random displacement to the circle center to get a point somewhere on the circle
		Vector2 displacement = { ((rand() % 201) - 100) / 100.0f, ((rand() % 201) - 100) / 100.0f };
		displacement = Vector2Scale(displacement, m_circleRadius);
		//Calculate the new wander destination
		m_WanderDestination = Vector2Add(circleCenter, displacement);
		//Clamp the destination on edge of screen
		//just so we don't 'wander' off screen i
		if (m_WanderDestination.x < 0)
		{
			m_WanderDestination.x = m_margin;
		}
		else if (m_WanderDestination.x > GetScreenWidth())
		{
			m_WanderDestination.x = GetScreenWidth() - m_margin;
		}
		if (m_WanderDestination.y < 0)
		{
			m_WanderDestination.y = m_margin;
		}
		else if (m_WanderDestination.y > GetScreenHeight())
		{
			m_WanderDestination.y = GetScreenHeight() - m_margin;
		}

		cout << "Calculating new wander target: " << m_WanderDestination.x << ", " << m_WanderDestination.y << endl;
		m_calculateNewTarget = false;
	}

	Vector2 dirToTarget = Vector2Subtract(m_WanderDestination, agent->GetPosition());

	//Are we near the wander target?
	if (Vector2Length(dirToTarget) < 1)
	{
		m_calculateNewTarget = true;
	}
	else
	{
		//Use a seeking behaviour to reach the m_WanderDestination
		Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(dirToTarget), agent->GetMaxSpeed());
		wanderForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());
	}

	return wanderForce;
//Original implementation which selects a new wander destination each frame
#else
	// The code to calculate the circle center:
	// m_circleDistance from the current agent position, in the same direction as the current velocity
	Vector2 circleCenter = Vector2Scale(Vector2Normalize(velocity), m_circleDistance);
	Vector2 displacement = { 0, -1 };
	displacement = Vector2Scale(displacement, m_circleRadius);
	//
	// Randomly change the vector direction
	// by making it change its current angle
	displacement = SetAngle(displacement, m_wanderAngle);
	//
	// Change wanderAngle just a bit, so it
	// won't have the same value in the
	// next game frame.	
	m_wanderAngle += (rand() % (int)m_angleChange) - m_angleChange * .5;
	Vector2 wanderForce = Vector2Add(circleCenter, displacement);
	/// DEBUG ONLY
	debug_cirleCenter = Vector2Add(agent->GetPosition(), circleCenter);
	debug_displacement = displacement;
	/// DEBUG ONLY
	return wanderForce;
#endif
#else
	return Vector2{ 0,0 };
#endif
}

void WanderForce::Draw(Agent* agent)
{
#if USE_WANDER_DESTINATION
#if 1
	DrawCircle(m_WanderDestination.x, m_WanderDestination.y, agent->GetSize(), BLUE);
#else
	DrawCircle(debug_cirleCenter.x, debug_cirleCenter.y, m_circleRadius, BLUE);
	DrawLine(debug_cirleCenter.x, debug_cirleCenter.y,
		debug_cirleCenter.x + debug_displacement.x, debug_cirleCenter.y + debug_displacement.y, MAGENTA);
#endif
#endif
}
