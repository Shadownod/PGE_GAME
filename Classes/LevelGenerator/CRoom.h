#ifndef CROOM_H
#define CROOM_H

#include <vector>
using std::vector;

class CCorridor;
class CRoomCoordinate;
enum Direction;

class CRoom
{
public:
	bool generated;
	bool firstRoom;
	int roomDepth;
	int xPos;                    // The x coordinate of the lower left tile of the room.
	int yPos;                    // The y coordinate of the lower left tile of the room.
	int roomWidth;               // How many tiles wide the room is.
	int roomHeight;              // How many tiles high the room is.

	Direction prevCorridor;         // The direction of the corridor that is entering this room.
	vector<CCorridor*> nextCorridors;   // The dir of the other corridors
	CRoomCoordinate* coordinate;

	CRoom();
	~CRoom();

	int SetupAllRoom(int _boardWidth, int _boardHeight, int _roomWidth, int _roomHeight, int _corridorLength, CRoomCoordinate* _startingCoord,
		int _maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors);

	cocos2d::Vec2 CenterPoint()
	{
		return cocos2d::Vec2(xPos + roomWidth * 0.5f, yPos + roomHeight * 0.5f);
	}


private:
	vector<CRoom*> GetEndRooms(vector<CRoom*> _rooms, int _depth);

	void SetupRoom(
		int _width, int _height, CRoomCoordinate* _roomCoordinate, CCorridor* _prevCorridor,
		int &_numRooms, int &_availableRooms, int &_maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors,
		int _depth, bool _ignoreDepth = false);
	void CreateEndRooms(
		int _width, int _height, int _corridorLength, vector<CRoom*> _endRooms,
		int &_numRooms, int &_availableRooms, int &_maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors);
	void SetupEndRoom(
		int _width, int _height, int _corridorLength,
		int &_numRooms, int &_availableRooms, int &_maxRooms, vector<vector<bool>> &_gameBoard, vector<CRoom*> &_rooms, vector<CCorridor*> &_corridors);


};

#endif