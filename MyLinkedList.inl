
/*****************************************************************************************/

//////////////////////////////////////////////////
//Default Constructor
//////////////////////////////////////////////////

template <class C>
inline
MyLinkedList<C>::MyLinkedList():
	m_head(0),
	m_tail(0)
{
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Destructor
//////////////////////////////////////////////////

template <class C>
inline
MyLinkedList<C>::~MyLinkedList(void)
{
	Clear();
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Clear all Data
//////////////////////////////////////////////////

template <class C>
inline void
MyLinkedList<C>::Clear()
{
	LinkedListNode<C>* entry = m_head;

	while (entry)
	{
		LinkedListNode<C>* release = entry;
		entry = entry->GetNext();
		delete release;
	}
	
	m_head = 0;
	m_tail = 0;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Remove element by data
//////////////////////////////////////////////////

template <class C>
inline void
MyLinkedList<C>::Remove(const C& Data)
{
	LinkedListNode<C>* entry = m_head;

	while (entry)
	{
		if (Data == entry->GetData())
		{
			Remove(entry);
			return;
		}
		entry = entry->GetNext();
	}
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Remove element by node
//////////////////////////////////////////////////

template <class C>
inline void
MyLinkedList<C>::Remove(LinkedListNode<C>* node)
{
	LinkedListNode<C>* prev = node->GetPrevious();
	LinkedListNode<C>* next = node->GetNext();

	if(prev)
	{
		prev->SetNext(next);
	}
	else
	{
		m_head = next;
	}

	if(next)
	{
		next->SetPrevious(prev);
	}
	else
	{
		m_tail = prev;
	}

	delete node;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Insert Data
//////////////////////////////////////////////////

template <class C>
inline void
MyLinkedList<C>::Insert(const C &Data)
{
	LinkedListNode<C>* node = new LinkedListNode<C>(Data);

	if(m_tail)
	{
		m_tail->SetNext(node);
		node->SetPrevious(m_tail);
		m_tail = node;
	}
	else
	{
		m_head = node;
		m_tail = node;
	}
}

/*****************************************************************************************/

template <class C>
inline void
MyLinkedList<C>::InsertAsHead(const C& Data)
{
	LinkedListNode<C>* node = new LinkedListNode<C>(Data);

	if(m_head)
	{
		m_head->SetPrevious(node);
		node->SetNext(m_head);
		m_head = node;
	}
	else
	{
		m_head = node;
		m_tail = node;
	}

}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Get First Element
//////////////////////////////////////////////////

template <class C>
inline LinkedListNode<C>*
MyLinkedList<C>::GetFirst() const
{
	return m_head;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Get Last Element
//////////////////////////////////////////////////

template <class C>
inline LinkedListNode<C>*
MyLinkedList<C>::GetLast() const
{
	return m_tail;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Get is list empty
//////////////////////////////////////////////////
template <class C>
inline bool
MyLinkedList<C>::IsEmpty() const
{
	return (m_head == 0);
}

/*****************************************************************************************/

