#ifndef _WAYPOINTMANAGER_H_
#define _WAYPOINTMANAGER_H_

#ifndef _SPHERE_H_
#include "Sphere.h"
#endif //#ifndef _SPHERE_H_

class WayPoint
{
public:
	MyString m_ID;
	Vector3D m_Position;
};

class WaypointManager : public Singleton<WaypointManager>
{
public:
	/**
	 * Constructor
	 */
						WaypointManager();
	/**
	 * Destructor
	 */
						~WaypointManager();
	/**
	 * Loads the way points from the specified file
	 */
	void				LoadWayPointFile(
							const char* wayPointFileName
							);
	/**
	 * Gets the waypoint with the specified id
	 */
	const WayPoint*		GetWayPoint(
							const char* ID
							) const;
	/**
	 * Returns the number of waypoints there are
	 */
	int					GetWayPointCount() const;
	/**
	 * Gets the waypoint at the specified index
	 */
	const WayPoint*		GetWayPoint(
							int index
							)  const;
private:
	static const int c_MaxWayPoints = 1024;
	WayPoint m_waypoints[c_MaxWayPoints];
	int m_numWaypoints;


};

#endif //_WAYPOINTMANAGER_H_
