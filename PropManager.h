#ifndef _PROPMANAGER_H
#define _PROPMANAGER_H

class PropItem;
class PropCollector;

class PropManager : public Singleton<PropManager>
{
public:
	/**
	 * Constructor
	 */
								PropManager();
	/**
	 * Destructor
	 */
								~PropManager();
	/**
	 * Adds an new prop
	 */
	void						AddProp(
									PropItem* propIn
									);
	/**
	 * Deletes a prop
	 */
	void						DeleteProp(
									PropItem* prop
									);
	/**
	 * Renders the props
	 */
	virtual void				Render();
	/**
	 * Updates the props
	 */
	void						Update(
									float elapsedTime
									);
	/**
	 * Gets the prop closest to a point
	 */
	PropItem*					GetClosestProp(
									const Vector3D& position
									);
	/**
	 * Gets the prop of a certain type closest to a point
	 */
	PropItem*					GetClosestOfType(
									const char* typeName, 
									const Vector3D& position
									);
	/**
	 * Gets the prop with the spcified id
	 */
	PropItem*					GetPropItem(
									const char* propID
									);
	/**
	 * Returns the number of props
	 */
	int							GetNumProps();
	/**
	 * Returns the prop at the specified index
	 */
	PropItem*					GetPropItem(
									int propIndex
									);
	/**
	 * Updates the id of a prop
	 */
	void						UpdateID(
									const char* oldName, 
									const char* newName
									);
	/**
	 * Updates the scale of a prop
	 */
	void						UpdateScale(
									const char* name, 
									float scale
									);
	/**
	 * Sets the object to use as the prop collector
	 */
	void						RegisterCollector(
									PropCollector* listener
									){m_propCollector = listener;}
	/**
	 * Returns the current 
	 */
	PropCollector*				GetCollector() {return m_propCollector;}
private:
	PropCollector* m_propCollector;
	
	static const int c_MaxPropItems = 512;
	PropItem* m_props[c_MaxPropItems];
	int m_numPropItems;
};


#endif