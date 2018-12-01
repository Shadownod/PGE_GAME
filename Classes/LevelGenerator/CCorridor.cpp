#include "CCorridor.h"
#include "CRoom.h"

void CCorridor::SetupCorridor(CRoom* _prevRoom, int length, Direction _direction)
{
	direction = _direction;
	prevRoom = _prevRoom;

	// Set a random length.
	corridorLength = length;

	switch (direction)
	{
		// If the choosen direction is NORTH (up)...
	case Direction::NORTH:
		// ... the starting position in the x axis can be random but within the width of the room.
		startXPos = _prevRoom->xPos + (_prevRoom->roomWidth / 2);
		startYPos = _prevRoom->yPos + _prevRoom->roomHeight;
		endRoomCoord = new CRoomCoordinate(prevRoom->coordinate->x, prevRoom->coordinate->y + 1);
		break;
	case Direction::EAST:
		startXPos = _prevRoom->xPos + _prevRoom->roomWidth;
		startYPos = _prevRoom->yPos + _prevRoom->roomHeight / 2;
		endRoomCoord = new CRoomCoordinate(prevRoom->coordinate->x + 1, prevRoom->coordinate->y);
		break;
	case Direction::SOUTH:
		startXPos = _prevRoom->xPos + _prevRoom->roomWidth / 2;
		startYPos = _prevRoom->yPos - 1;
		endRoomCoord = new CRoomCoordinate(prevRoom->coordinate->x, prevRoom->coordinate->y - 1);
		break;
	case Direction::WEST:
		startXPos = _prevRoom->xPos - 1;
		startYPos = _prevRoom->yPos + _prevRoom->roomHeight / 2;
		endRoomCoord = new CRoomCoordinate(prevRoom->coordinate->x - 1, prevRoom->coordinate->y);
		break;
	}
}