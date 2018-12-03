/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "LoadScreen.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"

USING_NS_CC;

Scene* LoadScreen::createScene()
{
	return LoadScreen::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoadScreenScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadScreen::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	if (!Scene::initWithPhysics())
	{
		return false;
	}

	getPhysicsWorld()->setDebugDrawMask(0xffff);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto label = Label::createWithTTF("Loading Next Scene", "fonts/Marker Felt.ttf", 24);

	if (label != nullptr)
	{
		//position the label on the center of the screen
		label->setPosition(Vec2((int)visibleSize.width >>1, (int)visibleSize.height >> 1));

		//add the label as a child to this layer
		this->addChild(label, 1);
	}

	this->scheduleUpdate();
	return true;
}

void LoadScreen::update(float delta)
{
	//auto scene = HelloWorld::createScene();
	//auto director = Director::getInstance();
	//return director->replaceScene(scene);

	SceneManager::Instance()->runScene("GoodBye");



	if (m_moveRight)
	{
	}

	if (m_moveLeft)
	{
	}

	if (m_moveUp)
	{
	}

	if (m_moveDown)
	{
	}

}

void LoadScreen::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void LoadScreen::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		if (!m_moveRight)
		{
			m_moveRight = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			PhysicsBody* curPhysics = curSprite->getPhysicsBody();
			curPhysics->setVelocity(Vec2(100.f, 0.f));
		}
		if (!m_animRight)
		{
			m_animRight = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			curSprite->runAction(RepeatForever::create(animateRight)->clone());
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		if (!m_moveLeft)
		{
			m_moveLeft = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			PhysicsBody* curPhysics = curSprite->getPhysicsBody();
			curPhysics->setVelocity(Vec2(-100.f, 0.f));
		}
		if (!m_animLeft)
		{
			m_animLeft = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			curSprite->runAction(RepeatForever::create(animateLeft)->clone());
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		if (!m_moveUp)
		{
			m_moveUp = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			PhysicsBody* curPhysics = curSprite->getPhysicsBody();
			curPhysics->setVelocity(Vec2(0.f, 100.f));
		}
		if (!m_animUp)
		{
			m_animUp = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			curSprite->runAction(RepeatForever::create(animateUp)->clone());
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (!m_moveDown)
		{
			m_moveDown = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			PhysicsBody* curPhysics = curSprite->getPhysicsBody();
			curPhysics->setVelocity(Vec2(0.f, -100.f));
		}
		if (!m_animDown)
		{
			m_animDown = true;

			auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
			curSprite->runAction(RepeatForever::create(animateDown)->clone());
		}
	}

}

void LoadScreen::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2::ZERO);
		curSprite->stopAllActions();

		m_moveRight = false;
		m_animRight = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2::ZERO);
		curSprite->stopAllActions();

		m_moveLeft = false;
		m_animLeft = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2::ZERO);
		curSprite->stopAllActions();

		m_moveUp = false;
		m_animUp = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2::ZERO);
		curSprite->stopAllActions();

		m_moveDown = false;
		m_animDown = false;
	}

}

void LoadScreen::onMouseMove(cocos2d::Event * event)
{
}

void LoadScreen::onMouseDown(cocos2d::Event * event)
{
}

void LoadScreen::onMouseUp(cocos2d::Event * event)
{
	EventMouse* e = (EventMouse*)event;
	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		//auto stopEvent = curSprite->getActionByTag(1337);
		curSprite->stopAllActions();

		curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveTo::create(5.f, Vec2(e->getCursorX(), e->getCursorY()));
		//moveEvent->setTag(1337);

		//lamda function to stop all action
		auto callbackStop = CallFunc::create([]()
		{
			auto scene = Director::getInstance()->getRunningScene();
			LoadScreen* helscene = (LoadScreen*)scene;
			auto curSprite = helscene->getPlayerSprite();
			curSprite->stopAllActions();
		});

		curSprite->runAction(RepeatForever::create(animateUp));
		auto sq = Sequence::create(moveEvent, callbackStop, animateDown, nullptr);
		curSprite->runAction(sq);

	}

}

void LoadScreen::onMouseScroll(cocos2d::Event * event)
{
}

bool LoadScreen::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	return true;
}
