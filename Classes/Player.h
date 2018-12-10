#pragma once

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

class Projectile;

enum MovementDir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

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
	bool onContactBegin(cocos2d::PhysicsContact & contact);

	void CheckProjContact(cocos2d::PhysicsContact & contact);

	void SetMovementSpd(float newSpd);
	void SetAtkValue(float newAtk);
	void SetMana(float newMana);
	void SetHealth(float newHealth);
	void SetDir(MovementDir dir);

	float GetMovementSpd();
	float GetAtkValue();
	float GetMana();
	float GetHealth();
	Sprite* GetSprite();
	MovementDir GetDir();

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
	MovementDir playerDir;

	std::vector<Projectile*> ProjList;
};

float getCurrentAngle(Node* node);
float getAngleDifference(float angle1, float angle2);
float getAngleBetweenVec(Point vec1, Point vec2);
void rotateNodeToPoint(Node* node, Point point);


