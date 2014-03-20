#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <assert.h>

template<class C>
class Singleton
{

public:
	/**
	 * Creates the singleton instance
	 */
	static C* Create()
	{
		Singleton<C>::m_currentInstance = ::new C;
		return Singleton<C>::m_currentInstance;
	}
	/**
	 * Destroys the singleton instance
	 */
	static void Destroy()
	{
		delete Singleton<C>::m_currentInstance;
		m_currentInstance = 0;
	}
	/**
	 * Returns the singleton instance
	 */
	static C* GetInstance()
	{
		return m_currentInstance;
	}

protected:
	static C* m_currentInstance;
};

#define DefineSingleton(C) C* Singleton<C>::m_currentInstance = 0;

#endif // _SINGLETON_H_