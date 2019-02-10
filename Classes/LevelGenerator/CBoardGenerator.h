#ifndef CBOARDGENERATOR_H
#define CBOARDGENERATOR_H

#include "cocos2d.h"

#include <vector>
using std::vector;

#include "CDungeonUtilities.h"

class Player;
class Enemy;

class CBoardGenerator
{
public:
	CBoardGenerator(int _boardWidth, int _boardHeight);
	~CBoardGenerator();

	void GenerateBoard(cocos2d::Node* _sceneFloorData);
	void SpawnPlayer(Player* _player, bool _randomPos = false);
	void SpawnEnemies(Enemy* _enemy, bool _randomPos = true);

private:
	void InstantiateTiles(cocos2d::Node* _sceneFloorData);
	void InstantiateWall(cocos2d::Node* _sceneFloorData, float xCoord, float yCoord);

	int boardWidth;
	int boardHeight;

	cocos2d::Sprite* wallSprite;
};

#endif