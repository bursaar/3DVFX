//Unlike the LinkedListNode, the HashTableKey does not store the data directly
//but contains a functions that can convert a protentually large piece of data
//into an index that can be used both quickly and effectiently to find required data.


/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Default Constructor
//////////////////////////////////////////////////////////////////
inline
HashTableKey::HashTableKey(void):
m_type(INT),
m_intValue(0),
m_stringLength(0)
{
}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//String Constructor
//////////////////////////////////////////////////////////////////
inline
HashTableKey::HashTableKey(const char* Key):
m_type(STRING),
m_stringLength(0)
{
	m_stringLength = strlen(Key) + 1;
	m_stringValue = Key;

}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Pointer Constructor
//////////////////////////////////////////////////////////////////
inline
HashTableKey::HashTableKey(const void *Key):
m_type(POINTER),
m_ptrValue(Key),
m_stringLength(0)
{

}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Int Constructor
//////////////////////////////////////////////////////////////////
inline
HashTableKey::HashTableKey(int Key):
m_type(INT),
m_intValue(Key),
m_stringLength(0)
{

}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Copy Constructor
//////////////////////////////////////////////////////////////////
inline
HashTableKey::HashTableKey(const HashTableKey &Key):
m_type(Key.m_type),
m_stringLength(Key.m_stringLength)
{
	switch (m_type)
	{
	case STRING:
		m_stringValue = Key.m_stringValue;
		break;
	case INT:
		m_intValue = Key.m_intValue;
		break;
	case POINTER:
		m_ptrValue = Key.m_ptrValue;
		break;
	}
}
/*****************************************************************************************/
inline
HashTableKey::~HashTableKey(void)
{

}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Compaires two strings for the same value
//////////////////////////////////////////////////////////////////
inline bool
HashTableKey::StringCompare(const HashTableKey &otherkey) const
{
	if (otherkey.m_stringValue == m_stringValue)
	{
		return true;
	}
	
	if (strcmp(m_stringValue, otherkey.m_stringValue) == 0)
	{
		return true;
	}	

	return false;
}	
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Equal to operator
//////////////////////////////////////////////////////////////////
inline bool
HashTableKey::operator ==(const HashTableKey &otherkey) const
{
	if(m_type == otherkey.m_type)
	{
		switch (m_type)
		{
			case STRING:
				if(StringCompare(otherkey))
				{
					return true;
				}
				break;
			case INT:
				if (m_intValue == otherkey.m_intValue)
				{
					return true;
				}
				break;
			case POINTER:
				if (m_ptrValue == otherkey.m_ptrValue)
				{
					return true;
				}
				break;
		}
	}
	return false;
}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//GetHash functions creates a hash key value with the data passed
//////////////////////////////////////////////////////////////////
inline unsigned __int32 
HashTableKey::GetHash(int HashSize)const
{
	unsigned __int32 slot = 0;

	switch (m_type)
	{
		case STRING:
			slot = 1159241;

			for (int i = 0; i < m_stringLength; i++)
			{
				char temp = m_stringValue[i];
				//remove case
				if (temp >= 'A' && temp <= 'Z')
				{
					temp -= 'A' - 'a';
				}

				slot ^= ( (slot << 5) + temp + (slot >> 2) );
			}
			slot = slot & 0x7fffffff;
			break;
		case INT:
			slot = m_intValue;
			break;
		case POINTER:
			slot = (unsigned __int32)((unsigned __int64)m_ptrValue) >> 2;
			break;
	}
	slot = slot % HashSize;
	return slot;
}
/*****************************************************************************************/
//////////////////////////////////////////////////////////////////
//Equals Operator
//////////////////////////////////////////////////////////////////
inline HashTableKey&
HashTableKey::operator =(const HashTableKey &otherkey)
{
	m_type = otherkey.m_type;
	m_stringLength = otherkey.m_stringLength;
	
	switch (m_type)
	{
	case STRING:
		m_stringValue = otherkey.m_stringValue;
		break;
	case INT:
		m_intValue = otherkey.m_intValue;
		break;
	case POINTER:
		m_ptrValue = otherkey.m_ptrValue;
		break;
	}

	return *this;
}
/*****************************************************************************************/
inline const char*
HashTableKey::GetKeyString()
{
	return m_stringValue;
}
/*****************************************************************************************/