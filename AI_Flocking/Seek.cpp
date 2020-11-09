#include "Seek.h"
#include "Agent.h"


Seek::Seek()
{
	m_targetPosition = nullptr;
}

Seek::~Seek()
{

}

void Seek::Update(Agent* agent, float a_deltaTime)
{
	if (m_targetPosition != nullptr)
	{
		// Get the distance between the target position and our position
		Vector2 distance = Vector2Subtract( *m_targetPosition , agent->GetPosition());

		if (Vector2Length(distance) > 0)
		{
			// Normalize the direction
			Vector2 normal = Vector2Normalize(distance);

			// Calculate the force that will be added this frame
			Vector2 force = Vector2Subtract(Vector2Scale(normal, agent->GetMaxSpeed()), agent->GetVelocity());

			// Make sure its within the specified bounds
			force = Vector2Scale(Vector2Normalize(force), a_deltaTime);

			// Add the force to the acceleration
			agent->AddForce(force);
		}
	}
}
