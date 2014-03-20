#ifndef _PROPCOLLECTOR_H_
#define _PROPCOLLECTOR_H_

#ifndef _TYPES_H_
#include "Types.h"
#endif //#ifndef _TYPES_H_

/**
 * anything that inherits this interface and registers with the Prop Manager can collect props
 * the OnCollected function needs to be overidden to tell the entity what to do
 * this way the propmanager library class doesn't need to be concerned with the game code
 */

class PropItem;

class PropCollector
{
public:
							PropCollector(){};

	virtual					~PropCollector(){};
	/**
	 * Interface to notify the collector that its picked up an item
	 */
	virtual void			OnCollected(
								PropItem* item ///< Prop that has been picked up
								) = 0;
	/**
	 * Returns the id of the prop collector
	 */
	const char*				GetID() const {return m_collectorID;}
protected:
	MyString m_collectorID;
};

#endif