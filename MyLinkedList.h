
#ifndef MyLinkedList_h
#define MyLinkedList_h

#include "LinkedListNode.h"

//////////////////////////////////////////////////////
//MyLinkedList
//
//This Class allows a list to be created, each element is linked
//to the both the next element and the previous within the list.
//this class is the container for the linked list, it allows
//you to add, remove and get data from the List
//////////////////////////////////////////////////////

template <class C>
class MyLinkedList
{
public:
	/**
	 * Constructor
	 */
	inline						MyLinkedList();
	/**
	 * Destructor
	 */
	inline						~MyLinkedList();
	/**
	 * Inserts a new element into the list
	 */
	inline void					Insert(
									const C& Data
									);
	/**
	 * Inserts a new element into the list at the head
	 */
	inline void					InsertAsHead(
									const C& Data
									);
	/**
	 * Removes all the elements from the list
	 */
	inline void					Clear();
	/**
	 * Removes a data element from the list
	 */
	inline void					Remove(
									const C& Data
									);
	/**
	 * Removes a specific element node from the list
	 */
	inline void					Remove(
									LinkedListNode<C>* node
									);
	/**
	 * Returns the first element node stroed within the list
	 */
	inline LinkedListNode<C>*	GetFirst() const;
	/**
	 * Returns the last element node stored within the list
	 */
	inline LinkedListNode<C>*	GetLast()const;
	/**
	 * Returns if there are no elements store within the list
	 */
	inline bool					IsEmpty() const;

private:
	/**
	 * Hide the copy constructor so that it wont be used
	 */
	inline						MyLinkedList(
									const MyLinkedList<C>& otherList
									) {};

	//Head and tail pointers
	LinkedListNode<C>* m_head;
	LinkedListNode<C>* m_tail;
};

#include "MyLinkedList.inl"

#endif 

