#ifndef CROOM_H
#define CROOM_H

#include "CCorridor.h"

class CRoom
{
public:
	int roomDepth;
	int xPos;                    // The x coordinate of the lower left tile of the room.
	int yPos;                    // The y coordinate of the lower left tile of the room.
	int roomWidth;               // How many tiles wide the room is.
	int roomHeight;              // How many tiles high the room is.

	Direction prevCorridor;         // The direction of the corridor that is entering this room.
	List<CCorridor> nextCorridors;   // The dir of the other corridors
	CRoomCoordinate coordinate;
	
	int SetupAllRoom(int _boardWidth, int _boardHeight, int _roomWidth, int _roomHeight, int _corridorLength, CRoomCoordinate _startingCoord,
		int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors);


private:
	List<CRoom> GetEndRooms(List<CRoom> _rooms, int _depth);

	void SetupRoom(int _width, int _height, CRoomCoordinate _roomCoordinate, CCorridor _prevCorridor,
		ref int _numRooms, ref int _availableRooms, ref int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors,
		int _depth, bool _ignoreDepth = false);
	void CreateEndRooms(int _width, int _height, int _corridorLength, List<CRoom> _endRooms,
		ref int _numRooms, ref int _availableRooms, ref int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors);
	void SetupEndRoom(int _width, int _height, int _corridorLength,
		ref int _numRooms, ref int _availableRooms, ref int _maxRooms, ref bool[][] _gameBoard, ref List<CRoom> _rooms, ref List<CCorridor> _corridors);

	bool generated;
	bool firstRoom;

};

#endif