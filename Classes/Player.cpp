#include "Player.h"
#include "Projectile.h"

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
	SetMovementSpd(100.f);
	SetAtkValue(10.f);
	SetDir(MovementDir::LEFT);

	xVelocity = yVelocity = 0.0f;

	playerSprite = Sprite::create("Blue_Front1.png");
	playerSprite->setAnchorPoint(Vec2::ZERO);
	playerSprite->setPosition(StartPos.x, StartPos.y);
	playerSprite->setName("PlayerSprite");
	playerSprite->setScaleX(0.5f);
	playerSprite->setScaleY(0.5f);

	playerNode = _playerNode;
	playerNode->addChild(playerSprite);

#pragma region Physics stuff
	auto playerBody = PhysicsBody::createBox(Size(playerSprite->getContentSize().width, playerSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.0f, 0.0f));
	
	playerSprite->addComponent(playerBody);
	playerPhysics = playerSprite->getPhysicsBody();
	playerPhysics->setDynamic(true);
	playerPhysics->setGravityEnable(false);
	playerPhysics->setRotationEnable(false);

	playerPhysics->setCategoryBitmask(0x01);



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
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		playerSprite->stopAllActions();
		xVelocity = -movementSpd;
		playerPhysics->setVelocity(Vec2(xVelocity,yVelocity));
		SetDir(MovementDir::LEFT);
		playerSprite->runAction(RepeatForever::create(moveLeftAnim));
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		playerSprite->stopAllActions();
		xVelocity = movementSpd;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
		SetDir(MovementDir::RIGHT);

		playerSprite->runAction(RepeatForever::create(moveRightAnim));

	}

	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		playerSprite->stopAllActions();
		yVelocity = movementSpd;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
		SetDir(MovementDir::UP);

	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		playerSprite->stopAllActions();
		yVelocity = -movementSpd;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
		SetDir(MovementDir::DOWN);
	}

}

void Player::onKeyRelease(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		playerSprite->stopAllActions();
		xVelocity = 0.0f;
		playerPhysics->setVelocity(Vec2(xVelocity, yVelocity));
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S)
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
		if (ProjList.size() < 20)
		{
			//Spawn projectile or something
			Projectile* bullet = new Projectile(playerDir, playerSprite->getPosition(), playerNode,200.0f);
			ProjList.push_back(bullet);
		}
		else
		{
			for (int i = 0; i < ProjList.size(); ++i)
			{
				if (!ProjList[i]->GetVisible())
				{
				ProjList[i]->ReSpawnBullet(playerDir, playerSprite->getPosition(), playerNode);
				cocos2d::log("CHECKVISIBLE");
				}
			}
		}
		
	}
	else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		//Do weapon skill stuff here
	}
}

bool Player::onContactBegin(cocos2d::PhysicsContact & contact)
{

	return true;
}

void Player::CheckProjContact(cocos2d::PhysicsContact & contact)
{
	for (int i = 0; i < ProjList.size(); ++i)
	{
		ProjList[i]->onContactBegin(contact);
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