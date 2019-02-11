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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "cocos/ui/CocosGUI.h"
#include "SceneManager.h"


USING_NS_CC;

#include "LevelGenerator/CBoardGenerator.h"

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

	/********************************
	********* Lab 01 Stuff **********
	********************************/
	//Set playing size which "splits" the playing area away from the setted area, 
	//anything that go above the playingSize will not appear on the screen
	cocos2d::Size playingSize = cocos2d::Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// "auto" automatically assigns the variable type when the variable is initialised.

	//***************
	//Floor Render
	//***************
#pragma region GameBoardGeneration

	auto nodeItems = Node::create();
	nodeItems->setName("gameBoard");
	nodeItems->setPosition(0, -50); // move the container together with all the items in it

	m_gameBoard = new CBoardGenerator(30, 20);
	m_gameBoard->GenerateBoard(nodeItems);

	this->addChild(nodeItems, 1);
#pragma endregion
	// UI
	auto exitbutton = ui::Button::create("ui/Exit.png", "ui/Exit_selected.png", "ui/Exit_disabled.png");
	exitbutton->addTouchEventListener([&](Ref* sender,
		ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			SceneManager::Instance()->runScene("GoodBye");
			break;
		default: break;
		} });

	exitbutton->setScale(0.5f);
	exitbutton->setPosition(cocos2d::Vec2(0 + exitbutton->getContentSize().width / 2, playingSize.height));
	exitbutton->setName("exitbutton");
	this->addChild(exitbutton);


	//Movable obj
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	player = new Player();
	player->Init(spriteNode, Vec2(0, 0));

	m_gameBoard->SpawnPlayer(player);


	this->addChild(spriteNode, 1);

#pragma region
	//auto EnemyNode = Node::create();
	//EnemyNode->setName("EnemyNode");
	//enemy = new Enemy;
	//enemy->Init(EnemyNode, Vec2(0, 0), player);

	//m_gameBoard->SpawnEnemies(enemy);


	//this->addChild(EnemyNode, 1);
#pragma endregion

	////autoMoving the sprite
	//int Destination = 1000;
	//auto moveEvent = MoveBy::create(5, Vec2(Destination, 0));
	//mainSprite->runAction(moveEvent);
	//
	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);

	/*****************************
	* Keyboard & Mouse Listeners *
	******************************/
	auto KBlistener = EventListenerKeyboard::create();
	KBlistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	KBlistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KBlistener, this);

	auto Mlistener = EventListenerMouse::create();
	Mlistener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMove, this);
	Mlistener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	Mlistener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	Mlistener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mlistener, this);

	/*****************************
	* Contact event Listener *
	******************************/
  	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);




	//Tell system that this "node"(scene) has a update
	this->scheduleUpdate();



	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	//
	// add a "close" icon to exit the progress. it's an autorelease object
	//auto closeItem = MenuItemImage::create(
	//                                       "CloseNormal.png",
	//                                       "CloseSelected.png",
	//                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//
	//if (closeItem == nullptr ||
	//    closeItem->getContentSize().width <= 0 ||
	//    closeItem->getContentSize().height <= 0)
	//{
	//    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	//}
	//else
	//{
	//    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
	//    float y = origin.y + closeItem->getContentSize().height/2;
	//    closeItem->setPosition(Vec2(x,y));
	//}
	//
	//// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);
	//
	/////////////////////////////
	// 3. add your codes below...
	//
	// add a label shows "Hello World"
	// create and initialize a label
	//
	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//if (label == nullptr)
	//{
	//    problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
	//    // position the label on the center of the screen
	//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
	//                            origin.y + visibleSize.height - label->getContentSize().height));
	//
	//    // add the label as a child to this layer
	//    this->addChild(label, 1);
	//}
	//
	//// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");
	//if (sprite == nullptr)
	//{
	//    problemLoading("'HelloWorld.png'");
	//}
	//else
	//{
	//    // position the sprite on the center of the screen
	//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//
	//    // add the sprite as a child to this layer
	//    this->addChild(sprite, 0);
	//}

	return true;
}

void HelloWorld::update(float delta)
{
	auto camera = Camera::getDefaultCamera();
	camera->setPosition(player->GetSprite()->getPosition());
	
	player->Update(delta);
	//if(enemy->GetSprite()->getPhysicsBody())
	//enemy->GetStateMachine()->Update();

}

void HelloWorld::menuCloseCallback(Ref* pSender)
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

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	player->onKeyPressed(keyCode, event);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	player->onKeyRelease(keyCode, event);
}

void HelloWorld::onMouseMove(Event * event)
{
}

void HelloWorld::onMouseDown(Event * event)
{
	player->onMouseDown(event);
}

void HelloWorld::onMouseUp(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	//if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	//{
	//	auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	//	//auto stopEvent = curSprite->getActionByTag(1337);
	//	curSprite->stopAllActions();
	//	curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	//	auto moveEvent = MoveTo::create(5.f, Vec2(e->getCursorX(), e->getCursorY()));
	//	//moveEvent->setTag(1337);
	//	
	//	//lamda function to stop all action
	//	auto callbackStop = CallFunc::create([]()
	//	{
	//		auto scene = Director::getInstance()->getRunningScene();
	//		HelloWorld* helscene = (HelloWorld*)scene;
	//		auto curSprite = helscene->getPlayerSprite();
	//		curSprite->stopAllActions();
	//	});
	//	curSprite->runAction(RepeatForever::create(animateUp));
	//	auto sq = Sequence::create(moveEvent, callbackStop, animateDown, nullptr);
	//	curSprite->runAction(sq);
	//}

}

void HelloWorld::onMouseScroll(Event * event)
{
}

bool HelloWorld::onContactBegin(PhysicsContact & contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	player->CheckProjContact(contact);
	cocos2d::log("CONTACT"); 
	player->onContactBegin(contact);
	return true;
}
