#ifndef CBOARDGENERATOR_H
#define CBOARDGENERATOR_H

#include "cocos2d.h"

#include <vector>
using std::vector;

#include "CDungeonUtilities.h"

class CBoardGenerator
{
public:
	CBoardGenerator(int _numRooms, int _roomWidth, int _roomHeight, int _corridorLength, int _boardColum, int _boardRow);
	~CBoardGenerator();

	void GenerateBoard(cocos2d::Node* _sceneFloorData);

private:
	void CreateNewFloor();
	bool CreateBoard(cocos2d::Node* _sceneFloorData, int _currentFloor);
	void InstantiateTiles(cocos2d::Node* _sceneFloorData, vector<vector<TileType>> _tiles);
	void InstantiateWall(cocos2d::Node* _sceneFloorData, float xCoord, float yCoord);

	int gridSize;

	int rooms;
	int roomWidth;
	int roomHeight;
	int corridorLength;
	int columns;  
	int rows;     

	int numFloors;
	int currFloor;

};

#endif