#ifndef _ASTAR_H_
#define _ASTAR_H_

#ifndef _TYPES_H_
#include "Types.h"
#endif //#ifndef _TYPES_H_

#ifndef __ASTARNODEQUEUE_H__
#include "AStarNodeQueue.h"
#endif //#ifndef __ASTARNODEQUEUE_H__

class AStarNode;

typedef MyLinkedList<AStarNode*> AStarPath;

/**
 * The AStar class implements the A* search alogrithm, it works on a generic set of AStar nodes which have 
 * the serach data embedded inside them to stop runtime alllocations and more effiecent searching. This also
 * means that the AStar path finder doesnt have to know anything about the nodes its searching over which means
 * we path find using this alogrithm over a whole range of different node types.
 */

class AStar : public Singleton<AStar>
{
public:
	/**
	 * Constructor
	 */
				AStar();
	/**
     * Destructor
	 */
				~AStar();
	/**
	 * Attempts to find a path between the 2 nodes returns true on success or false if no path can be found
	 * The resulting path will be stored within the path container passed in. If maxNodes != 0 the path finding
	 * will be aborted once the path gets upto the specified number of nodes ( populating the path up until that
	 * point)
	 */
	bool		FindPath(
					AStarNode* startNode, ///< The starting node
					AStarNode* endNode, ///< The end node
					AStarPath& resultingPath, ///< The resulting path
					int maxNodes = 0 ///< The maximum number of nodes for the path
					);
private:
	/**
	 * Builds the path from the current static node search data.
	 */
	void		BuildPath(
					AStarNode* endNode, ///< The node to which we have path found to
					AStarPath& resultingPath ///< The resulting path
					);

	AStarNodeQueue m_openList;
	int m_sessionId;
};

#define pAStar AStar::GetInstance()

#endif// __ASTAR_H__
