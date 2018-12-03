#include "Player.h"
USING_NS_CC_MATH;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Node* _playerNode,Vec2 StartPos)
{
	SetHealth(100.f);
	SetMana(100.f);
	SetMovementSpd(50.f);
	SetAtkValue(10.f);

	xVelocity = yVelocity = 0.0f;

	playerSprite = Sprite::create("Blue_Front1.png");
	playerSprite->setAnchorPoint(Vec2::ZERO);
	playerSprite->setPosition(StartPos.x, StartPos.y);
	playerSprite->setName("PlayerSprite");
	
	playerNode = _playerNode;
	playerNode->addChild(playerSprite);

#pragma region Physics stuff
	auto playerBody = PhysicsBody::createBox(Size(playerSprite->getContentSize().width, playerSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
	
	playerSprite->addComponent(playerBody);
	playerPhysics = playerSprite->getPhysicsBody();
	playerPhysics->setGravityEnable(false);
	playerPhysics->setRotationEnable(false);
	playerPhysics->setCategoryBitmask(0x01);
	playerPhysics->setCollisionBitmask(0x02);	//Collide with wall

#pragma endregion

#pragma region Animation frames
	//Move left	
	Vector<SpriteFrame*> animLeft;
	animLeft.reserve(4);
	animLeft.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(1, 1, 59, 81)));
	animLeft.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 59, 81)));
	animLeft.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 59, 81)));
	animLeft.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 59, 81)));

	Animation* animationLeft = Animation::createWithSpriteFrames(animLeft, 0.5f);
	moveLeftAnim = Animate::create(animationLeft);
	moveLeftAnim->retain();

	//Move right
	Vector<SpriteFrame*> animRight;
	animRight.reserve(4);
	animRight.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 65, 81)));
	animRight.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
	animRight.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 65, 81)));
	animRight.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));

	Animation* animationRight = Animation::createWithSpriteFrames(animRight, 0.5f);
	moveRightAnim = Animate::create(animationRight);
	moveRightAnim->retain();
#pragma endregion
}

void Player::Update(float dt)
{

	cocos2d::log("PLAYER VELOCITY: %u", playerPhysics->getVelocity().UNIT_X);
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		playerSprite->stopAllActions();
		xVelocity = -100.0f;
		playerPhysics->setVelocity(Vec2(xVelocity,yVelocity));
		SetDir(MovementDir::LEFT);
		playerSprite->runAction(RepeatForever::create(moveLeftAnim));
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		playerSprite->stopAllActions();
		xVelocity = 100.0f;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
		SetDir(MovementDir::RIGHT);

		playerSprite->runAction(RepeatForever::create(moveRightAnim));

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		playerSprite->stopAllActions();
		yVelocity = 100.0f;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
		SetDir(MovementDir::UP);

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		playerSprite->stopAllActions();
		yVelocity = 100.0f;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
		SetDir(MovementDir::DOWN);
	}

}

void Player::onKeyRelease(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		playerSprite->stopAllActions();
		xVelocity = 0.0f;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		playerSprite->stopAllActions();
		yVelocity = 0.0f;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
	}
}


void Player::onMouseDown(Event * event)
{

	EventMouse* e = (EventMouse*)event;	

	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{

		//Spawn projectile or something
		auto sprite = Sprite::create("Default_Projectile.png");
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		sprite->setPosition(playerSprite->getPosition());

		PhysicsBody* bulletBody;
		

		playerNode->addChild(sprite);
		switch (playerDir)
		{
		case UP:
			bulletBody = PhysicsBody::createBox(Size(sprite->getContentSize().height, sprite->getContentSize().width), PhysicsMaterial(0.001f, 0.0f, 0.0f));
			sprite->setRotation(90);
			bulletBody->setVelocity(Vec2(0, 10));
			break;
		case DOWN:
			bulletBody = PhysicsBody::createBox(Size(sprite->getContentSize().height, sprite->getContentSize().width), PhysicsMaterial(0.001f, 0.0f, 0.0f));
			sprite->setRotation(-90);
			bulletBody->setVelocity(Vec2(0, -10));
			break;
		case LEFT:
			bulletBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
			sprite->setRotation(0);
			bulletBody->setVelocity(Vec2(-10, 0));
			break;
		case RIGHT:
			bulletBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
			sprite->setRotation(180);
			bulletBody->setVelocity(Vec2(10, 0));
			break;
		default:
			break;
		}

		bulletBody->setGravityEnable(false);
		bulletBody->setRotationEnable(false);
		bulletBody->setCategoryBitmask(0x03);
		bulletBody->setCollisionBitmask(0x02);	//Collide with wall
		bulletBody->setGroup(-0x01);	//Prevent self Collision
		sprite->addComponent(bulletBody);


		////cursor to player
		//Vec2 dir = e->getLocation() - playerSprite->getPosition();
		////dir.normalize();
		//float rotation = CC_RADIANS_TO_DEGREES(atan2f(dir.y,dir.x));
	 
		//cocos2d::log("Rotation: %f", rotation);

		////TRY
		//playerNode->addChild(sprite);

		//auto spriteWorldSpace = sprite->getParent()->convertToWorldSpace(sprite->getPosition());

		//auto angle = atan2(e->getLocation().y - spriteWorldSpace.y, e->getLocation().x - spriteWorldSpace.y);
		//sprite->setRotation(CC_RADIANS_TO_DEGREES(-angle) + 90);

		//Try2
		//sprite->
		//Vec2 spritePos = sprite->getParent()->convertToNodeSpace(sprite->getPosition());
		//Vec2 dir = e->getLocation() - sprite->getPosition();
		
		//float angle = CC_RADIANS_TO_DEGREES(atan2(dir.y, dir.x));
		//cocos2d::log("angle: %f + CurX: %f + CurY: %f", angle,e->getLocation().x, e->getLocation().y);
		//cocos2d::log("Sprite posX: %f posY: %f", sprite->getPosition().x, sprite->getPosition().y);
		//sprite->setRotation(angle);
	
		//sprite->set(rotation);
	}
	else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		//Do weapon skill stuff here
	}
}

void Player::SetMovementSpd(float newSpd)
{
	movementSpd = newSpd;	
}

void Player::SetAtkValue(float newAtk)
{
	atkValue = newAtk;
}

void Player::SetMana(float newMana)
{
	mana = newMana;
}

void Player::SetHealth(float newHealth)
{
	health = newHealth;
}

void Player::SetDir(MovementDir dir)
{
	playerDir = dir;
}

float Player::GetMovementSpd()
{
	return movementSpd;
}

float Player::GetAtkValue()
{
	return atkValue;
}

float Player::GetMana()
{
	return mana;
}

float Player::GetHealth()
{
	return health;
}

Sprite * Player::GetSprite()
{
	return playerSprite;
}

MovementDir Player::GetDir()
{
	return playerDir;
}

void Player::AddMovementSpd(float addSpd)
{
	movementSpd += addSpd;
}

void Player::AddAtkValue(float addAtk)
{
	atkValue += addAtk;
}

void Player::AddMana(float addMana)
{
	mana += addMana;	
}

void Player::AddHealth(float addHeatlh)
{
	health += addHeatlh;
}

void Player::ReduceMovementSpd(float reduceSpd)
{
	movementSpd -= reduceSpd;
}

void Player::ReduceAtk(float reduceAtk)
{
	atkValue -= reduceAtk;
}

void Player::ReduceMana(float reduceMana)
{
	mana -= reduceMana;
}

void Player::ReduceHealth(float reduceHealth)
{
	health -= reduceHealth;
}

float getCurrentAngle(Node* node)
{
	float rotAngle = node->getRotation();
	if (rotAngle >= 180.0f)
		rotAngle -= 360.0f;
	else if (rotAngle < -180.0f)
		rotAngle += 360.0f;
	return rotAngle;
}

float getAngleDifference(float angle1, float angle2)
{
	float diffAngle = (angle1 - angle2);
	if (diffAngle >= 180.0f)
		diffAngle -= 360.0f;
	else if (diffAngle < -180.0f)
		diffAngle += 360.0f;

	return diffAngle;
	
}

float getAngleBetweenVec(Point vec1, Point vec2)
{
	auto vec1tovec2 = vec2 - vec1;
	return CC_RADIANS_TO_DEGREES(-vec1tovec2.getAngle());
}

void rotateNodeToPoint(Node* node, Point point)
{
	float angleNodeToRotateTo = getAngleBetweenVec(node->getAnchorPoint(), point);
	float nodeCurrentAngle = getCurrentAngle(node);
	float diffAngle = getAngleDifference(angleNodeToRotateTo, nodeCurrentAngle);

	float rotation = nodeCurrentAngle + diffAngle;
	cocos2d::log("ROTATION: %f", rotation);
	node->setRotation(rotation);
}