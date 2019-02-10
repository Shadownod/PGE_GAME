#include "CBoardGenerator.h"

#include "CDungeon.h"
#include "Player.h";
#include "Enemy.h";

CBoardGenerator::CBoardGenerator(int _boardWidth = 50, int _boardHeight = 50)
	: boardWidth(_boardWidth)
	, boardHeight(_boardHeight)
{
	wallSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
}

CBoardGenerator::~CBoardGenerator()
{
}

void CBoardGenerator::GenerateBoard(cocos2d::Node* _sceneFloorData)
{
	// get board
	if (_sceneFloorData == nullptr)
	{
		return;
	}

	InstantiateTiles(_sceneFloorData);
}

void CBoardGenerator::InstantiateTiles(cocos2d::Node* _sceneFloorData)
{
	//Horizontal
	for (int i = 0; i < boardWidth; ++i)
	{
		InstantiateWall(_sceneFloorData, i, 0);
		InstantiateWall(_sceneFloorData, i, boardHeight  - 1);
	}
	//Vertical
	for (int i = 0; i < boardHeight; ++i)
	{
		InstantiateWall(_sceneFloorData, 0, i);
		InstantiateWall(_sceneFloorData, boardWidth - 1, i);
	}

	//// Go through all the tiles in the jagged array...
	//for (int i = 0; i < _tiles.size(); i++)
	//{
	//	for (int j = 0; j < _tiles[i].size(); j++)
	//	{
	//		// If the tile type is Wall...
	//		switch (_tiles[i][j])
	//		{
	//		case TileType::Wall:
	//			// instantiate a wall.
	//			InstantiateWall(_sceneFloorData, i, j);
	//			break;
	//
	//		//case TileType::Floor:
	//		//	// instantiate a floor
	//		//	InstantiateFromArray(floorTiles, i, j);
	//		//	break;
	//		}
	//	}
	//}
}

USING_NS_CC;

void CBoardGenerator::InstantiateWall(cocos2d::Node* _sceneFloorData, float xCoord, float yCoord)
{
	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	sprite->setAnchorPoint(Vec2::ZERO); // Vec2::ZERO == Vec2(0,0)
	sprite->setPosition(xCoord * sprite->getContentSize().width, yCoord * sprite->getContentSize().height);

	//Create a static PhysicsBody
	auto physicsBody = cocos2d::PhysicsBody::createBox(
		cocos2d::Size(sprite->getContentSize().width, sprite->getContentSize().height),
		PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(0x02);	
	physicsBody->setCollisionBitmask(0x07);
	physicsBody->setContactTestBitmask(0x03);


	sprite->addComponent(physicsBody);

	_sceneFloorData->addChild(sprite, 0);
}

void CBoardGenerator::SpawnPlayer(Player* _player, bool _randomPos)
{
	cocos2d::Vec2 SpawnPoint;
	if (_randomPos)
		SpawnPoint = Vec2(random(1, boardWidth - 2), random(1, boardHeight - 2));
	else
		SpawnPoint = Vec2(boardWidth * 0.5f, boardHeight * 0.5f);

	//_player->GetSprite ? ->GetPosition ? = the line below
	_player->GetSprite()->setPosition(
	Vec2(SpawnPoint.x * wallSprite->getContentSize().width, SpawnPoint.y * wallSprite->getContentSize().height));
	
}

void CBoardGenerator::SpawnEnemies(Enemy * _enemy, bool _randomPos)
{
	cocos2d::Vec2 SpawnPoint;
	if (_randomPos)
		SpawnPoint = Vec2(random(1, boardWidth - 2), random(1, boardHeight - 2));
	else
		SpawnPoint = Vec2(boardWidth * 0.5f, boardHeight * 0.5f);

	//_player->GetSprite ? ->GetPosition ? = the line below
	_enemy->GetSprite()->setPosition(
		Vec2(SpawnPoint.x * wallSprite->getContentSize().width, SpawnPoint.y * wallSprite->getContentSize().height));
}

