#pragma once

#include "cocos2d.h"
#include "StateMachine.h"
#include "StateChase.h"
#include "StateIdle.h"
USING_NS_CC;

class Player;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(Node* _enemyNode, Vec2 StartPos);
	void Update(float dt);

	void SetMovementSpd(float newSpd);
	void SetAtkValue(float newAtk);
	void SetMana(float newMana);
	void SetHealth(float newHealth);
	void SetAlert(bool status);

	float GetMovementSpd();
	float GetAtkValue();
	float GetMana();
	float GetHealth();
	Sprite* GetSprite();
	bool GetAlert();

	void AddMovementSpd(float addSpd);
	void AddAtkValue(float addAtk);
	void AddMana(float addMana);
	void AddHealth(float addHeatlh);

	void ReduceMovementSpd(float reduceSpd);
	void ReduceAtk(float reduceAtk);
	void ReduceMana(float reduceMana);
	void ReduceHealth(float reduceHealth);

	void CheckDistance(Player* _playerobj);

	StateMachine* GetStateMachine();

private:
	float movementSpd;
	float atkValue;
	float mana;
	float health;
	float xVelocity, yVelocity;

	bool alerted;

	PhysicsBody* enemyPhysics;
	Sprite* enemySprite;
	StateMachine* statemachine;


	//Probably change it to a weapon class or something sure
	Sprite* defaultProjectile;
	Animate* moveLeftAnim;
	Animate* moveRightAnim;
	Node* enemyNode;
};

float getCurrentAngle(Node* node);
float getAngleDifference(float angle1, float angle2);
float getAngleBetweenVec(Point vec1, Point vec2);
void rotateNodeToPoint(Node* node, Point point);


