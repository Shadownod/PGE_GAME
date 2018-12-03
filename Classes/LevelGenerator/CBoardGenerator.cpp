#include "CBoardGenerator.h"

#include "CDungeon.h"
#include "CFloor.h";
#include "CRoom.h";
#include "CCorridor.h";
#include "Player.h"

CBoardGenerator::CBoardGenerator(int _numRooms, int _roomWidth, int _roomHeight, int _corridorLength, int _boardColum, int _boardRow)
	: rooms(_numRooms)
	, roomWidth(_roomWidth)
	, roomHeight(_roomHeight)
	, corridorLength(_corridorLength)
	, columns(_boardColum)
	, rows(_boardRow)
{
	numFloors = 100;
	wallSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
}

CBoardGenerator::~CBoardGenerator()
{
}

void CBoardGenerator::GenerateBoard(cocos2d::Node* _sceneFloorData)
{
	gridSize = rooms / 2;
	if (gridSize * gridSize <= rooms)
		gridSize += gridSize;
	columns = gridSize * (roomWidth + corridorLength) + 2 * (roomWidth + corridorLength);
	rows = gridSize * (roomHeight + corridorLength) + 2 * (roomHeight + corridorLength);

	currFloor = CDungeon::getInstance()->currentFloor;

	if (currFloor <= 0)
	{
		currFloor = 1;
		CDungeon::getInstance()->currentFloor = currFloor;
	}

	CreateNewFloor();
	CreateBoard(_sceneFloorData, currFloor);
}

void CBoardGenerator::CreateNewFloor()
{
	CFloor* temp = new CFloor();
	temp->setName("Floor_" + std::to_string(currFloor));
	temp->InitNewLevel(columns, rows, rooms, gridSize, roomWidth, roomHeight, corridorLength);

	CDungeon::getInstance()->AddNewFloor(currFloor, temp);
}

bool CBoardGenerator::CreateBoard(cocos2d::Node* _sceneFloorData, int _currentFloor)
{
	// get board
	if (_sceneFloorData == nullptr)
	{
		return false;
	}

	if (_currentFloor <= 0) // Floor must be > 0
		return false;

	InstantiateTiles(_sceneFloorData, CDungeon::getInstance()->floors[_currentFloor - 1]->GetTiles());
	return true;
}

void CBoardGenerator::InstantiateTiles(cocos2d::Node* _sceneFloorData, vector<vector<TileType>> _tiles)
{
	// Go through all the tiles in the jagged array...
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			// If the tile type is Wall...
			switch (_tiles[i][j])
			{
			case TileType::Wall:
				// instantiate a wall.
				InstantiateWall(_sceneFloorData, i, j);
				break;

			//case TileType::Floor:
			//	// instantiate a floor
			//	InstantiateFromArray(floorTiles, i, j);
			//	break;
			}
		}
	}
}

//void CBoardGenerator::InstantiateFromArray(GameObject[] prefabs, float xCoord, float yCoord)
//{
//	// Create a random index for the array.
//	int randomIndex = Random.Range(0, prefabs.Length);

//	// The position to be instantiated at is based on the coordinates.
//	Vector3 position = new Vector3(xCoord, yCoord, 0f);

//	// Create an instance of the prefab from the random index of the array.
//	GameObject tileInstance = Instantiate(prefabs[randomIndex], position, Quaternion.identity, boardHolder.transform) as GameObject;
//}

USING_NS_CC;

void CBoardGenerator::InstantiateWall(cocos2d::Node* _sceneFloorData, float xCoord, float yCoord)
{
	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	sprite->setAnchorPoint(Vec2::ZERO); // Vec2::ZERO == Vec2(0,0)
	sprite->setPosition(xCoord * sprite->getContentSize().width, yCoord * sprite->getContentSize().height);

	//Create a static PhysicsBody
	auto physicsBody = cocos2d::PhysicsBody::createBox(
		cocos2d::Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(0x02);
	physicsBody->setCollisionBitmask(0x01);
	sprite->addComponent(physicsBody);

	_sceneFloorData->addChild(sprite, 0);
}

void CBoardGenerator::SpawnPlayer(Player* _player, int _whichRoom)
{
	cocos2d::Vec2 roomCenterPoint = CDungeon::getInstance()->floors[CDungeon::getInstance()->currentFloor - 1]->GetRooms()[_whichRoom]->CenterPoint();
	//_player->GetSprite ? ->GetPosition ? = the line below
	_player->GetSprite()->setPosition(
	Vec2(roomCenterPoint.x * wallSprite->getContentSize().width, roomCenterPoint.y * wallSprite->getContentSize().height));
	
}

