#include "MoveBehaviour.h"
#include "NodeMap.h"

extern NodeMap* map;

MoveBehaviour::MoveBehaviour()
{

}

MoveBehaviour::~MoveBehaviour()
{
}

void MoveBehaviour::Update(Agent* agent, float deltaTime)
{
	if (theTrailWeBlaze.size() != 0)
	{
		if (agent->GetPosition().x <= targetNode->position.x + 20 && agent->GetPosition().x >= targetNode->position.x - 20)
		{
			if (agent->GetPosition().y <= targetNode->position.y + 20 && agent->GetPosition().y >= targetNode->position.y - 20)
			{
				theTrailWeBlaze.erase(theTrailWeBlaze.begin());

				if (theTrailWeBlaze.size() != 0)
				{
					targetNode = *theTrailWeBlaze.begin();
				}
			}
		}
	}
	else
	{
		if (agent->GetPosition().x <= targetNode->position.x + 20 && agent->GetPosition().x >= targetNode->position.x - 20)
		{
			if (agent->GetPosition().y <= targetNode->position.y + 20 && agent->GetPosition().y >= targetNode->position.y - 20)
			{
				if (canWander)
				{
					Wander();
				}
			}
		}
	}

	Vector2 v = Vector2Subtract(targetNode->position, agent->GetPosition());

	if (v.x == 0 && v.y == 0)
	{
		// if seeker on top of target, v is 0 so following calculations are not needed
		return;
	}

	Vector2 desiredVelocity;
	if (Vector2Length(v) < agent->GetMaxSpeed())
	{
		desiredVelocity = v;
	}
	else
	{
		desiredVelocity = Vector2Scale(Vector2Normalize(v), agent->GetMaxSpeed());
	}
	Vector2 steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());

	agent->AddForce(steeringForce);
}

void MoveBehaviour::Wander()
{
	for (int i = 0; i < targetNode->connections.size(); i++)
	{
		if (targetNode->connections[i].target->isGround)
		{
			walkWays++;
		}
	}

	int pathway = rand() % walkWays;
	walkWays = 0;

	for (int i = 0; i < targetNode->connections.size(); i++)
	{
		if (targetNode->connections[i].target->isGround)
		{
			if (walkWays == pathway)
			{
				targetNode = targetNode->connections[i].target;
				return;
			}
			walkWays++;
		}
	}
}

void MoveBehaviour::Seek(NodeMap::Node* m_destination)
{
	theTrailWeBlaze = map->DijkstrasSearch(targetNode, m_destination);
	theTrailWeBlaze.pop_back();
}
