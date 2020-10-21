#include "SeekBehaviour.h"

bool SeekBehaviour::Update(Agent* agent, float deltaTime)
{
	Vector2 v = Vector2Subtract(m_destination, agent->GetPosition());

	if (v.x == 0 && v.y == 0)
	{
		// if seeker on top of target, v is 0 so following calculations are not needed
		return true;
	}

	Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), agent->GetMaxSpeed());
	Vector2 steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());

	agent->AddForce(steeringForce);

	return true;
}

#include "Agent.h"
#include "SeekForce.h"

//Vector2 SeekForce::Update(Agent* agent, float deltaTime)
//{
//	Vector2 dirToTarget = Vector2Subtract(m_Target, agent->GetPosition());
//	//Update the desired acceleration/force requested by this Steeringforce
//	return Vector2Scale(Vector2Normalize(dirToTarget), m_SteeringAcceleration);
//}
