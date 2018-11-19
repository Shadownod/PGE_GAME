#ifndef CDUNGEONUTILITIES_H
#define CDUNGEONUTILITIES_H

class CRoomCoordinate
{
	int x;
	int y;

	CRoomCoordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	CRoomCoordinate(const CRoomCoordinate &_mirror)
	{
		x = _mirror.x;
		y = _mirror.y;
	}

	void setCoordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

/******************
 * General Codes
 ******************/

enum Direction
{
	// Do not change this arrangement
	NORTH, EAST, SOUTH, WEST, Size
};

#endif