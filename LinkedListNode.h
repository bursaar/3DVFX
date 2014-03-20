#ifndef LinkedListNode_h
#define LinkedListNode_h

/////////////////////////////////////////////////
//LinkedListNode is used as each element within the 
//linked list, when a node is created, the List Container
//assigns the data to the class (the data can be any class as linkedList is a Template class)
//the container also sets pointers to the previous and next elements within the conatiner if
//they exist.
/////////////////////////////////////////////////

template <class C> class MyLinkedList;

template <class C>
class LinkedListNode
{
public:
	/**
	 * Constructor
	 */
	inline					LinkedListNode();
	/**
	 * Constructor from data type
	 */
	inline					LinkedListNode(
								const C& data
								);
	/**
	 * Destructor
	 */
	inline					~LinkedListNode();
	/**
	 * Returns the linked list node before this one
	 */
	inline LinkedListNode*	GetPrevious() const;
	/**
	 * Returns the linked list node after this one
	 */
	inline LinkedListNode*	GetNext() const;
	/**
	 * Returns the data stored within this node
	 */
	inline C&				GetData();
	/**
	 * Sets the node before this node
	 */
	inline void				SetPrevious(
								LinkedListNode* previous
								);
	/**
	 * Sets the node before this node
	 */
	inline void				SetNext(
								LinkedListNode* next
								);
private:
	//variables
	C m_this;
	LinkedListNode* m_previous;
	LinkedListNode* m_next;

};

#include "LinkedListNode.inl"

#endif //LinkedListNode_h
