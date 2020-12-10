#pragma once
#include "IBehaviour.h"
#include "NodeMap.h"
#include <vector>

class MoveBehaviour :
	public IBehaviour
{
public:
	MoveBehaviour();
	virtual ~MoveBehaviour();

	virtual void Update(Agent* agent, float deltaTime);

	void Wander();
	void Seek(NodeMap::Node* m_destination);

	NodeMap::Node* targetNode;
	vector<NodeMap::Node*> theTrailWeBlaze;
	int walkWays = 0;
	bool canWander = true;
	
	void SetDestination(NodeMap::Node* m_destination) { targetNode = m_destination; }
};

