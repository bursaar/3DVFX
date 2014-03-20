#include "Types.h"
#include "MyFileReader.h"
#include "WaypointManager.h"

/****************************************************************************************************/

DefineSingleton(WaypointManager);

/****************************************************************************************************/

WaypointManager::WaypointManager() :
	m_numWaypoints(0)
{
}

/****************************************************************************************************/

WaypointManager::~WaypointManager()
{
}

/****************************************************************************************************/

void
WaypointManager::LoadWayPointFile(const char *wayPointFileName)
{
	MyFileReader reader;

	if(reader.Exists(wayPointFileName))
	{
		reader.OpenFile(wayPointFileName,"r");

		MyString Id = reader.GetNextToken();
		float x = (float)atof(reader.GetNextToken());
		float y = (float)atof(reader.GetNextToken());
		float z = (float)atof(reader.GetNextToken());

		while (Id[0] != '\0')
		{
			assert(m_numWaypoints < c_MaxWayPoints);
			WayPoint& waypoint = m_waypoints[m_numWaypoints];
			waypoint.m_ID = Id;
			waypoint.m_Position = Vector3D(x,y,z);
			m_numWaypoints ++;

			Id = reader.GetNextToken();
			x = (float)atof(reader.GetNextToken());
			y = (float)atof(reader.GetNextToken());
			z = (float)atof(reader.GetNextToken());

		}

		reader.CloseFile();
	}
	else
	{
		ErrorMessage("Waypoint File Could not be found");

	}
}

/****************************************************************************************************/

const WayPoint*
WaypointManager::GetWayPoint(const char* ID) const
{
	for (int index = 0; index < m_numWaypoints; index ++)
	{
		const WayPoint& waypoint = m_waypoints[index];
		
		if(strcmp(ID,waypoint.m_ID) == 0)
		{
			return &waypoint;
		}
	}

	return 0;
}

/****************************************************************************************************/

int
WaypointManager::GetWayPointCount() const
{
	return m_numWaypoints;
}

const WayPoint*
WaypointManager::GetWayPoint(int index) const
{
	if(index < m_numWaypoints)
	{
		return &m_waypoints[index];
	}

	return NULL;
}

/****************************************************************************************************/