#pragma once
#include "IBehaviour.h"
#include "Blackboard.h"
#include "Agent.h"

// behaviour that responds to questions this entity can answer
class BlackboardRespondBehaviour : public IBehaviour {
public:

	BlackboardRespondBehaviour(Blackboard* blackboard) : m_blackboard(blackboard) {}
	virtual ~BlackboardRespondBehaviour() {}

	virtual eBehaviourResult Execute(Agent* agent, float deltaTime);

protected:

	Blackboard* m_blackboard;
};