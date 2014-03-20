#include "Types.h"

#include "AStarNode.h"
#include "AStarNodeQueue.h"

/****************************************************************************************************/

AStarNodeQueue::AStarNodeQueue() :
	m_listHead(0)
{
}

/****************************************************************************************************/

AStarNodeQueue::~AStarNodeQueue()
{
}

/****************************************************************************************************/

void 
AStarNodeQueue::Push(AStarNode* item)
{
	item->m_nextNode = m_listHead;
	item->m_isOpen = true;
	m_listHead = item;
}

/****************************************************************************************************/

void 
AStarNodeQueue::Pop(AStarNode*& item)
{
	// Search the whole list and return node with best score
	if (m_listHead)
	{
		AStarNode* bestNodePrev = NULL;
		AStarNode* bestNode = m_listHead;
		float bestScore = bestNode->GetTotalEstimatedCost();

		AStarNode* prevNode = m_listHead;
		AStarNode* currentNode = m_listHead->m_nextNode;

		while (currentNode)
		{
			float nodeScore = currentNode->GetTotalEstimatedCost();

			if (nodeScore < bestScore)
			{
				bestScore = nodeScore;
				bestNode = currentNode;
				bestNodePrev = prevNode;
			}

			prevNode = currentNode;
			currentNode = currentNode->m_nextNode;
		}

		// Cut out best node
		if (bestNodePrev)
		{
			bestNodePrev->m_nextNode = bestNode->m_nextNode;
		}
		else
		{
			m_listHead = bestNode->m_nextNode;
		}

		bestNode->m_nextNode = NULL;
		bestNode->m_isOpen = false;
		item = bestNode;
	}
	else
	{
		item = NULL;
	}
}

/****************************************************************************************************/

bool
AStarNodeQueue::IsEmpty() const
{
	return m_listHead == NULL;
}

/****************************************************************************************************/

void
AStarNodeQueue::Clear()
{
	m_listHead = NULL;
}

/****************************************************************************************************/
