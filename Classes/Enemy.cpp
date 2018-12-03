#include "Enemy.h"

void Enemy::Init(Node * _enemyNode, Vec2 StartPos)
{
	SetHealth(100.f);
	SetMana(100.f);
	SetMovementSpd(50.f);
	SetAtkValue(10.f);

	xVelocity = yVelocity = 0.0f;

	enemySprite = Sprite::create("Blue_Front1.png");
	enemySprite->setAnchorPoint(Vec2::ZERO);
	enemySprite->setPosition(StartPos.x, StartPos.y);
	enemySprite->setName("EnemySprite");

	enemyNode = _enemyNode;
	enemyNode->addChild(enemySprite);


#pragma region Physics stuff
	auto enemyBody = PhysicsBody::createBox(Size(enemySprite->getContentSize().width, enemySprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));

	enemySprite->addComponent(enemyBody);
	enemyPhysics = enemySprite->getPhysicsBody();
	enemyPhysics->setGravityEnable(false);
	enemyPhysics->setRotationEnable(false);
#pragma endregion
}

void Enemy::Update(float dt)
{
}

void Enemy::SetMovementSpd(float newSpd)
{
	movementSpd = newSpd;
}

void Enemy::SetAtkValue(float newAtk)
{
	atkValue = newAtk;
}

void Enemy::SetMana(float newMana)
{
	mana = newMana;
}

void Enemy::SetHealth(float newHealth)
{
	health = newHealth;
}

float Enemy::GetMovementSpd()
{
	return movementSpd;
}

float Enemy::GetAtkValue()
{
	return atkValue;
}

float Enemy::GetMana()
{
	return mana;
}

float Enemy::GetHealth()
{
	return health;
}

Sprite * Enemy::GetSprite()
{
	return enemySprite;
}

void Enemy::AddMovementSpd(float addSpd)
{
	movementSpd += addSpd;
}

void Enemy::AddAtkValue(float addAtk)
{
	atkValue += addAtk;
}

void Enemy::AddAtkValue(float addAtk)
{
	atkValue += addAtk;
}

void Enemy::AddMana(float addMana)
{
	mana += addMana;
}

void Enemy::AddHealth(float addHeatlh)
{
	health += addHeatlh;
}

void Enemy::ReduceMovementSpd(float reduceSpd)
{
	movementSpd -= reduceSpd;
}

void Enemy::ReduceAtk(float reduceAtk)
{
	atkValue -= reduceAtk;
}

void Enemy::ReduceMana(float reduceMana)
{
	mana -= reduceMana;
}

void Enemy::ReduceHealth(float reduceHealth)
{
	health -= reduceHealth;
}
