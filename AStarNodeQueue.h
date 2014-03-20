#ifndef __ASTARNODEQUEUE_H__
#define __ASTARNODEQUEUE_H__

/**
 * The AStarNodeQueue is utiliased by the AStar class to store a list of open nodes fro the current path finding
 * operation. It stores the nodes using an emebbeded node list which is stored within the nodes and searches 
 * through these nodes, finding the node with the lowest score, when the AStar class requests the next node.
 */

class AStarNode;

class AStarNodeQueue
{
public:
	/**
	 * Constructor
	 */
				AStarNodeQueue();
	/**
	 * Destructor
	 */
				~AStarNodeQueue();
	/**
	 * Inserts a new A star node into the queue
	 */
	void		Push(
					AStarNode* item ///< The node to insert
					);
	/**
	 * Gets the node with the lowest total score from the queue
	 */
	void		Pop(
					AStarNode*& item ///< The node with the lowest score
					);
	/**
	 * Returns is there are no nodes stored within the queue
	 */
	bool		IsEmpty() const;
	/**
	 * Clears the queue
	 */
	void		Clear();

private:
	AStarNode* m_listHead;
};

#endif //#ifndef __ASTARNODEQUEUE_H__
