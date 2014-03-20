#include "LinkedListNode.h"

/*****************************************************************************************/

/////////////////////////////////////////////////
//Default Constructor
/////////////////////////////////////////////////

template <class C>
inline
LinkedListNode<C>::LinkedListNode() :
	m_previous(0),
	m_next(0),
	m_this(0)
{
}

/*****************************************************************************************/

/////////////////////////////////////////////////
//Constructor with data parameter
/////////////////////////////////////////////////

template<class C>
inline
LinkedListNode<C>::LinkedListNode(const C& data) :
	m_previous(0),
	m_next(0),
	m_this(data)
{
}

/*****************************************************************************************/

/////////////////////////////////////////////////
//Destructor
/////////////////////////////////////////////////

template <class C>
inline
LinkedListNode<C>::~LinkedListNode(void)
{
}

/*****************************************************************************************/

/////////////////////////////////////////////////
//Get Previous Pointer (the element before this one)
/////////////////////////////////////////////////

template <class C>
inline
LinkedListNode<C>* 
LinkedListNode<C>::GetPrevious() const
{
	return m_previous;
}

/*****************************************************************************************/

/////////////////////////////////////////////////
//Get Next Pointer (the element after this one, if one exists)
/////////////////////////////////////////////////

template <class C>
inline
LinkedListNode<C>* 
LinkedListNode<C>::GetNext() const
{
	return m_next;
}
/*****************************************************************************************/

/////////////////////////////////////////////////
//Get Data within this element
/////////////////////////////////////////////////

template <class C>
inline C& 
LinkedListNode<C>::GetData()
{
	return m_this;
}

/*****************************************************************************************/

/////////////////////////////////////////////////
//Set Previous Pointer
/////////////////////////////////////////////////

template <class C>
inline void
LinkedListNode<C>::SetPrevious(LinkedListNode* previous)
{
	m_previous = previous;
}

/*****************************************************************************************/

/////////////////////////////////////////////////
//Set Next Pointer
/////////////////////////////////////////////////

template <class C>
inline void
LinkedListNode<C>::SetNext(LinkedListNode* next)
{
	m_next = next;
}

/*****************************************************************************************/

