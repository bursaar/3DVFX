#ifndef _MYHASHTABLE_H_
#define _MYHASHTABLE_H_
#include "HashTableKey.h"

//////////////////////////////////////////////////////
//MyHashTable
//
//With a structure on the lines of Linked List, the MyHashTable class is a container for
//Hash Table Entries, The class contains the HashEntry structure, which is used to contain
//The hash key and data, the array of HashEntry and various gets and set.
//this hash table is also linked through, for easy access of data.
//////////////////////////////////////////////////////

//Defines for NORESIZE, a full 8-bit values and NULL POINTER, and empty value
#define NORESIZE 0xffffffff
#define NULLPTR 0x00000000

template <class C>
class MyHashTable
{
public:
	/**
	 * Constructor
	 */
	inline					MyHashTable(
								int initialSize, ///< The initial number of hashing slots
								int max ///< The maximum number of entries per a hashing slots
								);
	/**
	 * Destructor
	 */
	inline					~MyHashTable();
	/**
	 * Insert a data element with the specified key
	 */
	inline void				Insert(
								const HashTableKey& key, ///< Key to store the data element under
								const C& data ///< The data to store
								);
	/**
	 * Remove an element with the specified key
	 */
	inline void				Remove(
								const HashTableKey& key ///< The data element key to remove
								);
	/**
	 * Return the data element for the specified key
	 */
	inline C&				Find(
								const HashTableKey& key ///< The data element key to find
								);
	/**
	 * Returns the first element stored within the hash table
	 */
	inline C&				GetFirst() const;
	/**
	 * Returns the next element stored within the hash table
	 */
	inline C&				GetNext() const;
	/**
	 * Removes all data stored within the hash table
	 */
	inline void				Clear();
private:
	/**
	 * Resizes the number of hasing slots.
	 */
	inline void					Rehash(
									int slots
									);

	// The HashEntry Structure, used to store a key and data
	struct HashEntry
	{
		HashTableKey m_hashKey;
		C m_data;
		HashEntry* m_next;
	};


	//Variables
	int m_hashSize;
	HashEntry** m_nodes;
	int m_numberOfEntries;
	int m_capacity;

	mutable int			m_getIndex;
	mutable HashEntry*	m_getItem;
};

#include "MyHashTable.inl"

#endif // _MYHASHTABLE_H_
