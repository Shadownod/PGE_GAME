//#ifndef CFLOOR_H
//#define CFLOOR_H
//
//#include <vector>
//using std::vector;
//#include <string>
//using std::string;
//
//class CRoom;
//class CCorridor;
//#include "CDungeonUtilities.h"
//
//class CFloor
//{
//public:
//	int columns;                                 // The number of columns on the board (how wide it will be).
//	int rows;                                    // The number of rows on the board (how tall it will be).
//	string levelName;
//
//	vector<vector<bool>> gameBoard;
//
//	vector<vector<TileType>> tiles;                          // A jagged array of tile types representing the board, like a grid.
//	vector<CRoom*> rooms;                                     // All the rooms that are created for this board.
//	vector<CCorridor*> corridors;                             // All the corridors that connect the rooms.
//	CRoomCoordinate* StartingRoom;
//
//	void InitNewLevel(int _columns, int _rows, int _numRooms, int _gridSize, int _roomWidth, int _roomHeight, int _corridorLength);
//	void SetupTilesArray();
//	void CreateRoomsAndCorridors(int _numRooms, int _roomWidth, int _roomHeight, int _corridorLength);
//	void SetTilesValuesForRooms();
//	void SetTilesValuesForCorridors();
//
//	vector<CRoom*> GetRooms()
//	{
//		return rooms;
//	}
//
//	vector<vector<TileType>> GetTiles()
//	{
//		return tiles;
//	}
//
//	string getName()
//	{
//		return levelName;
//	}
//
//	void setName(string _value)
//	{
//		levelName = _value;
//	}
//};
//
//#endif