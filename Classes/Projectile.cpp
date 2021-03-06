#include "Projectile.h"
#include "Player.h"
#include "math/CCMathBase.h"
Projectile::Projectile()
{
}

Projectile::Projectile(MovementDir _PlayerDir, Vec2 playerPos,Node* spriteNode,float _Speed, float _Damage, float _LifeSpan)
{
	Speed = _Speed;
	Damage = _Damage;
	LifeSpan = _LifeSpan;

	//Spawn projectile or something
	projSprite = Sprite::create("Default_Projectile.png");
	projSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	projSprite->setPosition(playerPos);
	projSprite->setScaleX(0.2f);
	projSprite->setScaleY(0.2f);
	spriteNode->addChild(projSprite);
	
	PhysicsBody* bulletBody;
	switch (_PlayerDir)
	{
	case UP:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().height, projSprite->getContentSize().width), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(90);
		bulletBody->setVelocity(Vec2(0, Speed));
		break;
	case DOWN:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().height, projSprite->getContentSize().width), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(-90);
		bulletBody->setVelocity(Vec2(0, -Speed));
		break;
	case LEFT:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().width, projSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(0);
		bulletBody->setVelocity(Vec2(-Speed, 0));
		break;
	case RIGHT:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().width, projSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(180);
		bulletBody->setVelocity(Vec2(Speed, 0));
		break;
	default:
		break;
	}

	bulletBody->setGravityEnable(false);
	bulletBody->setRotationEnable(false);
	bulletBody->setCategoryBitmask(0x03);
	bulletBody->setCollisionBitmask(0x06);	//Collide with AI

	bulletBody->setGroup(-0x01);	//Prevent self Collision

	bulletBody->setContactTestBitmask(0x06);
	
	bulletBody->setDynamic(true);
	bulletBody->setGravityEnable(false);
	projSprite->addComponent(bulletBody);

	isActive = true;
}

Projectile::~Projectile()
{
}

void Projectile::Update(float _dt)
{
	if (!isActive)
		return;
	LifeSpan -= _dt;
	if (LifeSpan <= 0)
	{
		isActive = false;
		projSprite->setVisible(false);
	}
	
}

bool Projectile::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

	if (bodyA->getNode() == projSprite && bodyB->getCategoryBitmask() == 0x02 || bodyB->getNode() == projSprite && bodyA->getCategoryBitmask() == 0x02)
	{
		projSprite->setVisible(false);
		projSprite->removeComponent(projSprite->getPhysicsBody());
		isActive = false;
	}
	else if (bodyA->getNode() == projSprite && bodyB->getCategoryBitmask() == 0x04 || bodyB->getNode() == projSprite && bodyA->getCategoryBitmask() == 0x04)
	{
		projSprite->setVisible(false);
		//projSprite->removeComponent(bulletBody);
		projSprite->removeComponent(projSprite->getPhysicsBody());

		if (bodyB->getCategoryBitmask() == 0x04)
		{
			Node* enemy = bodyB->getOwner();
			enemy->setVisible(false);
			enemy->removeComponent(enemy->getPhysicsBody());
		}
		else
		{
			Node* enemy = bodyA->getOwner();
			enemy->setVisible(false);
			enemy->removeComponent(enemy->getPhysicsBody());
		}
		isActive = false;
	}

	return true;
}

void Projectile::SetSpeed(float _Speed)
{
	this->Speed = _Speed;
}

void Projectile::SetDamage(float _Damage)
{
	this->Damage = _Damage;
}

void Projectile::SetLifeSpan(float _LifeSpan)
{
	this->LifeSpan = _LifeSpan;
}

float Projectile::GetSpeed()
{
	return this->Speed;
}

float Projectile::GetDamage()
{
	return this->Damage;
}

float Projectile::GetLifeSpan()
{
	return this->LifeSpan;
}

bool Projectile::GetActive()
{
	return isActive;
}

void Projectile::ReSpawnBullet(MovementDir _PlayerDir, Vec2 playerPos, float _Speed, float _Damage, float _LifeSpan)
{
	Speed = _Speed;
	Damage = _Damage;
	LifeSpan = _LifeSpan;

	projSprite->setVisible(true);
	projSprite->setPosition(playerPos);

	PhysicsBody* bulletBody;
	switch (_PlayerDir)
	{
	case UP:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().height, projSprite->getContentSize().width), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		
		projSprite->setRotation(90);
		bulletBody->setVelocity(Vec2(0, Speed));
		break;
	case DOWN:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().height, projSprite->getContentSize().width), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(-90);
		bulletBody->setVelocity(Vec2(0, -Speed));
		break;
	case LEFT:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().width, projSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(0);
		bulletBody->setVelocity(Vec2(-Speed, 0));
		break;
	case RIGHT:
		bulletBody = PhysicsBody::createBox(Size(projSprite->getContentSize().width, projSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
		projSprite->setRotation(180);
		bulletBody->setVelocity(Vec2(Speed, 0));
		break;
	default:
		break;
	}

	bulletBody->setGravityEnable(false);
	bulletBody->setRotationEnable(false);
	bulletBody->setCategoryBitmask(0x03);
	bulletBody->setCollisionBitmask(0x06);	//Collide with wall
	bulletBody->setGroup(-0x01);	//Prevent self Collision
	bulletBody->setContactTestBitmask(0x06);
	bulletBody->setDynamic(true);
	bulletBody->setGravityEnable(false);
	if (projSprite->getPhysicsBody() == nullptr)
		projSprite->addComponent(bulletBody);

	isActive = true;
}
