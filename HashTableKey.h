#ifndef _HASHTABLEKEY_H_
#define _HASHTABLEKEY_H_
#include <string.h>

//////////////////////////////////////////////////////////////////
//HashTableKey
//
//This function converts a large, possibly variable-sized amount of data into a small datum 
//which can be used as a key. the key can then be used as an accessor to data contained within
//The hash table,
//
//There are Three types of key, a string type, and integer type and a Pointer type
//This will return the key value for the hash table to use
//////////////////////////////////////////////////////////////////

class HashTableKey
{
public:
	//Key Type
	enum Type
	{
		STRING = 1,
		POINTER,
		INT,
	};

	/**
	 * Constructor
	 */
	inline						HashTableKey();
	/**
	 * Construct the key from an int
	 */
	inline						HashTableKey(
									int Key
									);
	/**
	 * Construct the key from a pointer
	 */
	inline						HashTableKey(
									const void* Key
									);
	/**
	 * Construct the key from a string
	 */
	inline						HashTableKey(
									const char* Key
									);
	/**
	 * Copy constructor
	 */
	inline						HashTableKey(
									const HashTableKey& Key
									);
	/**
	 * Destructor
	 */
	inline						~HashTableKey();

	/**
	 * Equals operator
	 */
	inline bool					operator == (
									const HashTableKey& otherkey
									) const;
	/**
	 * Assignment operator
	 */
	inline HashTableKey&		operator = (
									const HashTableKey& otherkey
									);
	/**
	 * Returns the slot for this key based upon the number of slots
	 */
	inline unsigned int			GetHash(
									int HashSize
									) const;

	inline bool StringCompare(const HashTableKey& otherkey) const;

	inline const char* GetKeyString();
	
	
	
private:

	int m_type;
	int m_stringLength;
	union
	{
		const void* m_ptrValue;
		const char* m_stringValue;
		int m_intValue;
	};

};

#include "HashTableKey.inl"
#endif //_HASHTABLEKEY_H_
