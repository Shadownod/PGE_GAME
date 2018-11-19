#ifndef CFLOOR_H
#define CFLOOR_H

#include "CCorridor.h"
#include "CRoom.h"
#include "CDungeonUtilities.h"

#include <vector>
using std::vector;
#include <string>
using std::string;

class CFloor
{
public:
	int columns;                                 // The number of columns on the board (how wide it will be).
	int rows;                                    // The number of rows on the board (how tall it will be).
	string levelName;

	bool gameBoard[1][1];

	TileType tiles[1][1];                               // A jagged array of tile types representing the board, like a grid.
	vector<CRoom> rooms;                                     // All the rooms that are created for this board.
	vector<CCorridor> corridors;                             // All the corridors that connect the rooms.
	CRoomCoordinate StartingRoom;

	void InitNewLevel(int _columns, int _rows, int _numRooms, int _gridSize, int _roomWidth, int _roomHeight, int _corridorLength);
	void SetupTilesArray();
	void CreateRoomsAndCorridors(int _numRooms, int _roomWidth, int _roomHeight, int _corridorLength);
	void SetTilesValuesForRooms();
	void SetTilesValuesForCorridors();

	vector<CRoom> GetRooms()
	{	return rooms; }

	TileType[][] GetTiles()
	{	return tiles; }

	string getName()
	{	return levelName; }

	void setName(string _value)
	{	levelName = _value;	}
};

#endif