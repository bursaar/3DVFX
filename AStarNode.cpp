#include "Types.h"

#include "AStarNode.h"

/****************************************************************************************************/

AStarNode::AStarNode() :
	m_sessionId(0)
{
}

/****************************************************************************************************/

AStarNode::~AStarNode()
{
}

/****************************************************************************************************/

void
AStarNode::InitialiseNode(int sessionId, AStarNode* parentNode, AStarNode* goalNode)
{
	if (m_sessionId != sessionId)
	{
		m_sessionId = sessionId;
		m_estCostToGoal = CostEstimate(goalNode);
	}

	m_isOpen = false;
	m_parent = parentNode;
	if (parentNode == NULL)
	{
		// we are the cell that contains the starting location of the A* search
		m_costFromStart = 0.0f;
		m_numParents = 0;
	}
	else
	{
		m_numParents = parentNode->GetPathLength() + 1;
		m_costFromStart = parentNode->GetCostFromStart() + CostCalculate(parentNode);
	}
	m_totalScore = m_costFromStart + m_estCostToGoal;
	m_nextNode = NULL;
}

/****************************************************************************************************/

AStarNode*
AStarNode::GetParent() const
{
	return m_parent;
}

/****************************************************************************************************/

int
AStarNode::GetSessionID() const
{
	return m_sessionId;
}

/****************************************************************************************************/

bool
AStarNode::IsOnOpenList() const
{
	return m_isOpen;
}

/****************************************************************************************************/

float
AStarNode::GetCostFromStart() const
{
	return m_costFromStart;
}

/****************************************************************************************************/

float
AStarNode::GetEstimatedCostToGoal() const
{
	return m_estCostToGoal;
}

/****************************************************************************************************/

float
AStarNode::GetTotalEstimatedCost() const
{
	return m_totalScore;
}

/****************************************************************************************************/

int
AStarNode::GetPathLength() const
{
	return m_numParents;
}

/****************************************************************************************************/

AStarNode*
AStarNode::GetNextNode() const
{
	return m_nextNode;
}

/****************************************************************************************************/

void
AStarNode::CheckForBetterPathFrom(AStarNode* parentNode)
{
	if (parentNode)
	{
		float arrivalCost = parentNode->GetCostFromStart() + CostCalculate(parentNode);

		if (arrivalCost < m_costFromStart)
		{
			m_costFromStart = arrivalCost;
			m_totalScore = arrivalCost + m_estCostToGoal;
			m_parent = parentNode;
		}
	}
}

/****************************************************************************************************/
