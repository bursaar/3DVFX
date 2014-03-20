#include "Types.h"

#include "AStarNode.h"
#include "AStar.h"

/*******************************************************************************************************/

DefineSingleton(AStar);

/****************************************************************************************************/

AStar::AStar() :
	m_sessionId(0)
{
}

/****************************************************************************************************/

AStar::~AStar()
{
}

/****************************************************************************************************/

bool 
AStar::FindPath(AStarNode* startNode, AStarNode* endNode, AStarPath& resultingPath, int maxNodes)
{
	bool foundPath = false;
	AStarNode* bestNode = NULL;
	
	m_openList.Clear();

	if (startNode)
	{
		m_sessionId++;

		// Push the start node onto the open list
		startNode->InitialiseNode(m_sessionId, NULL, endNode);
		m_openList.Push(startNode);

		// Process the open list until empty (We'll break out if a path is found)
		while(!m_openList.IsEmpty())
		{
			// Pop the open cell with the lowest cost from the open list
			AStarNode* parentNode;
			m_openList.Pop(parentNode);

			// If this cell is our Goal Node, we are done
			if (parentNode == endNode)
			{
				bestNode = parentNode;
				foundPath = true;
				break;
			}

			// Store off the best node found so far
			if (!bestNode || parentNode->GetEstimatedCostToGoal() < bestNode->GetEstimatedCostToGoal())
			{
				bestNode = parentNode;			
			}

			// If we have made too many iterations, quit out and build a partial path
			if (maxNodes && bestNode->GetPathLength() > maxNodes)
			{
				BuildPath(bestNode, resultingPath);
				return false;
			}

			// Query the neigbours to see if they need to be added to the Open heap
			AStarNode* neighbourNode = parentNode->GetFirstNeighbour();
			while(neighbourNode)
			{
				if (neighbourNode->GetSessionID() != m_sessionId)
				{
					// This is a new session, reset our internal data
					neighbourNode->InitialiseNode(m_sessionId, parentNode, endNode);

					// Add neighbour cell to the Open heap
					m_openList.Push(neighbourNode);
				}
				else if (neighbourNode->IsOnOpenList())
				{
					// Neighbour is already in the Open Heap. Check if this node provides a better path to it
					neighbourNode->CheckForBetterPathFrom(parentNode);
				}

				// Get next neighbour
				neighbourNode = parentNode->GetNextNeighbour();
			}
		}
	}

	//build the path if we have one
	if (foundPath)
	{
		BuildPath(bestNode, resultingPath);
	}
	else
	{
		resultingPath.Clear();
	}

	return foundPath;
}

/****************************************************************************************************/

void	
AStar::BuildPath(AStarNode* endNode, AStarPath& resultingPath)
{
	resultingPath.Clear();

	AStarNode* currentNode = endNode;

	while (currentNode)
	{
		resultingPath.InsertAsHead(currentNode);
		currentNode = currentNode->GetParent();
	}

}

/****************************************************************************************************/
