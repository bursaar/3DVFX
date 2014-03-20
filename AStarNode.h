#ifndef _ASTARNODE_H_
#define _ASTARNODE_H_

class AStarNode
{
public:
	/**
	 * Constructor
	 */
						AStarNode();
	/**
	 * Destructor
	 */
	virtual				~AStarNode();
	/**
	 * Calculates the cost from moving from this node to the node 
	 * passed in.
	 *
	 * \returns The cost for moving between the nodes
	 */
	virtual float		CostCalculate(
							AStarNode* to
							) = 0;
	/**
	 * Estimates the cost from moving from this node to the node 
	 * passed in.
	 *
	 * \returns The estimate for moving between the nodes
	 */
	virtual float		CostEstimate(
							AStarNode* to
							) = 0;
	/**
	 * Initialises neighbour iteration 
	 *
	 * \returns The first neighbour of the node or NULL if no neighbours
	 */
	virtual AStarNode*	GetFirstNeighbour() = 0;
	/**
	 * Progresses neighbour iteration
	 *
	 * \returns The next neighbour of the node or NULL if no more neighbours
	 */
	virtual AStarNode*	GetNextNeighbour() = 0;
	/** 
	 * \returns the node's sessionid 
	 */
	int					GetSessionID() const;
	/**	
	 * \returns The previous node on the found path
	 */
	AStarNode*			GetParent() const;
	/**	
	 * \returns The calculated cost of path from start to this node
	 */
	float				GetCostFromStart() const;

	/**
	 * \returns The estimated cost of path from this node to goal node
	 */
	float				GetEstimatedCostToGoal() const;
	
	/**
	 * \returns The summed figures of costFromStart and estimatedCostToGoal
	 */
	float				GetTotalEstimatedCost() const;
	
	/**	
	 * \returns true if node is on the open list - otherwise false.
	 */
	bool				IsOnOpenList() const;

	/**
	 * Called the first time the node is visited in search 
	 * It calculates the costs to it and estimates costs to goal
	 * and setup sessionid and parent pathnode.
	 */
	void				InitialiseNode(
							int sessionId, 
							AStarNode* parentNode, 
							AStarNode* goalNode
							);
	/**
	 * This function is called when it is already on the openlist and is being visited
	 * again along a different path.
	 * 
	 * This function tests if the new path is better than the old one and if so
	 * adjusts the path costs and resultant path.
	 */
	void				CheckForBetterPathFrom(
							AStarNode* parentNode
							);
	/**
	 * returns the number of parents of the node on a current path
	 * Only makes sense during an astar search
	 * Its used to control early exit from astar .
	 */
	int					GetPathLength() const;
	/**
	 * Returns the next node in the path queue.
	 */
	AStarNode*			GetNextNode() const;
private:
	friend class AStarNodeQueue;

	AStarNode*	m_parent;			///< The node that we arrived from on path
	float		m_costFromStart;	///< Actual cheapest cost of arriving to this node from the start
	float		m_totalScore;		///< The total estimated score of path running through this node.
	bool		m_isOpen;			///< Is the node on the open list or not
	int			m_numParents;		///< Num of nodes preceding in path

	AStarNode*	m_nextNode;			///< next node in the singly linked list in the AStarQueue

	int			m_sessionId;		///< Used to see if a node had been touched. Also allows us to only reset nodes as we visit them.
	float		m_estCostToGoal;	///< Heuristic estimate of the cost to the goal from this node
};

#endif
