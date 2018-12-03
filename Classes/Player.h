#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Player
{
public:
	Player();
	~Player();

	void Init(Node* playerNode,Vec2 StartPos);
	void Update(float dt);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyRelease(EventKeyboard::KeyCode keyCode, Event * event);
	void onMouseDown(Event* event);

	void SetMovementSpd(float newSpd);
	void SetAtkValue(float newAtk);
	void SetMana(float newMana);
	void SetHealth(float newHealth);

	float GetMovementSpd();
	float GetAtkValue();
	float GetMana();
	float GetHealth();
	Sprite* GetSprite();

	void AddMovementSpd(float addSpd);
	void AddAtkValue(float addAtk);
	void AddMana(float addMana);
	void AddHealth(float addHeatlh);

	void ReduceMovementSpd(float reduceSpd);
	void ReduceAtk(float reduceAtk);
	void ReduceMana(float reduceMana);
	void ReduceHealth(float reduceHealth);

private:
	float movementSpd;
	float atkValue;
	float mana;
	float health;
	float xVelocity, yVelocity;

	PhysicsBody* playerPhysics;
	Sprite* playerSprite;

	//Probably change it to a weapon class or something 
	Sprite* Weapon1;
	Sprite* Weapon2;
	Sprite* defaultProjectile;
	Animate* moveLeftAnim;
	Animate* moveRightAnim;
	Node* playerNode;
};

float getCurrentAngle(Node* node);
float getAngleDifference(float angle1, float angle2);
float getAngleBetweenVec(Point vec1, Point vec2);
void rotateNodeToPoint(Node* node, Point point);


