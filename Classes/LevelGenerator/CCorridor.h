#ifndef CCORRIDOR_H
#define CCORRIDOR_H
#include "CDungeonUtilities.h"

class CRoom;

class CCorridor
{
public:
	bool connectedTo;
	int startXPos;         // The x coordinate for the start of the corridor.
	int startYPos;         // The y coordinate for the start of the corridor.
	int corridorLength;    // How many units long the corridor is.
	Direction direction;   // Which direction the corridor is heading from it's room.

	CRoomCoordinate* endRoomCoord;
	CRoom* prevRoom;

	int getEndPositionX()
	{
			if (direction == Direction::NORTH || direction == Direction::SOUTH)
				return startXPos;
			if (direction == Direction::EAST)
				return startXPos + corridorLength - 1;
			return startXPos - corridorLength + 1;
	};

	int getEndPositionY()
	{
		if (direction == Direction::EAST || direction == Direction::WEST)
			return startYPos;
		if (direction == Direction::NORTH)
			return startYPos + corridorLength - 1;
		return startYPos - corridorLength + 1;
	};

	void SetupCorridor(CRoom* _prevRoom, int length, Direction _direction);
};

#endif