
/*****************************************************************************************/

//////////////////////////////////////////////////
//Constructor
//////////////////////////////////////////////////

template <class C>
MyHashTable<C>::MyHashTable(int initialSize, int max):
	m_hashSize(0),
	m_nodes(0),
	m_numberOfEntries(0),
	m_capacity(max),
	m_getIndex(0),
	m_getItem(0)
{
	Rehash(initialSize);
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Destructor
//////////////////////////////////////////////////

template <class C>
MyHashTable<C>::~MyHashTable()
{
	Clear();

	if (m_nodes)
	{
		delete [] m_nodes;
		m_nodes = 0;
	}
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Rehash sorts the elements within the hash table
//if the table is resized or altered
//////////////////////////////////////////////////

template <class C>
inline void 
MyHashTable<C>::Rehash(int slots)
{
	HashEntry** old = m_nodes;
	int oldnum = m_hashSize;

	m_nodes = new HashEntry*[slots];
	memset(m_nodes,0,sizeof(HashEntry*)*slots);
	m_hashSize = slots;

	for (int i = 0; i < oldnum; i++)
	{
		HashEntry * entry = old[i];

		while(entry)
		{
			HashEntry* rehash = entry;
			entry = entry->m_next;
			int newslot = rehash->m_hashKey.GetHash(m_hashSize);
			rehash->m_next = m_nodes[newslot];
			m_nodes[newslot] = rehash;
		}
	}

	if (old)
	{
		delete [] old;
	}
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Insert Element
//////////////////////////////////////////////////

template <class C>
inline void 
MyHashTable<C>::Insert(const HashTableKey& key, const C& data)
{
	if(m_capacity != NORESIZE)
	{
		int count = (m_numberOfEntries + 1)/ m_hashSize;

		if(count > m_capacity)
		{
			int numslots = (m_hashSize << 1) + 1;
			Rehash(numslots);
		}
	}
	
	unsigned __int32 slot = key.GetHash(m_hashSize);
	HashEntry* entry = m_nodes[slot];
	while (entry)
	{
		if(entry->m_hashKey == key)
		{
			return;
		}
		entry = entry->m_next;
	}

	HashEntry* newEntry = new HashEntry;
	newEntry->m_hashKey = key;
	newEntry->m_data = data;
	m_numberOfEntries++;
	newEntry->m_next = m_nodes[slot];
	m_nodes[slot] = newEntry;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Remove Element
//////////////////////////////////////////////////

template <class C>
inline void 
MyHashTable<C>::Remove(const HashTableKey& key)
{
	int slot = key.GetHash(m_hashSize);

	HashEntry* entry = m_nodes[slot];
	HashEntry* prev = 0;

	while (entry)
	{
		if (entry->m_Key == key)
		{
			if(prev)
			{
				prev->m_next = entry->m_next;
			}
			else
			{
				m_nodes[slot] = entry->m_next;
			}
			delete entry;
			m_numberOfEntries--;
			return;
		}
		prev = entry;
		entry = entry->m_next;
	}
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Find element in table
//////////////////////////////////////////////////

template <class C>
inline C&
MyHashTable<C>::Find(const HashTableKey& key)
{
	int slot = key.GetHash(m_hashSize);

	HashEntry* entry = m_nodes[slot];

	while(entry)
	{
		if (entry->m_hashKey == key)
		{
			return entry->m_data;
		}
		entry = entry->m_next;
	}

	static C ptr = 0;
	return ptr;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Get First Element
//////////////////////////////////////////////////

template <class C>
inline C&
MyHashTable<C>::GetFirst() const
{
	m_getIndex = 0;
	m_getItem = m_nodes[m_getIndex];
	
	while(!m_getItem)
	{
		m_getIndex++;

		if (m_getIndex == m_hashSize)
		{
			static C ptr = 0;
			return ptr;
		}
		m_getItem = m_nodes[m_getIndex];
	}
	return m_getItem->m_data;
}

/*****************************************************************************************/

//////////////////////////////////////////////////
//Get the Next Element
//////////////////////////////////////////////////

template <class C>
inline C&
MyHashTable<C>::GetNext()  const
{
	if(!m_getItem)
	{
		C* ptr = 0;
		return *ptr;
	}

	m_getItem = m_getItem->m_next;
	while (!m_getItem)
	{
		m_getIndex++;

		if (m_getIndex == m_hashSize)
		{
			m_getItem = 0;
			static C ptr = 0;
			return ptr;
		}
		
		m_getItem = m_nodes[m_getIndex];
	}

	return m_getItem->m_data;
}

/*****************************************************************************************/

template <class C>
inline void				
MyHashTable<C>::Clear()
{
	for (int index = 0; index < m_hashSize; index ++)
	{
		HashEntry* entry = m_nodes[index];

		while (entry)
		{
			HashEntry* prev = entry;
			entry = entry->m_next;
			delete prev;
		}
		m_nodes[index] = 0;
	}
	
	m_numberOfEntries = 0;
}

/*****************************************************************************************/