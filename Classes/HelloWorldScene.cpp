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

USING_NS_CC;

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/********************************
	********* Lab 01 Stuff **********
	********************************/
	//Set playing size which "splits" the playing area away from the setted area, 
	//anything that go above the playingSize will not appear on the screen
	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// "auto" automatically assigns the variable type when the variable is initialised.

	//Floor Render
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	nodeItems->setPosition(0, -50); // move the container together with all the items in it

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");

	int howmany = playingSize.width / sprite->getContentSize().width;
	int SpawnX = 0;
	int SpawnY = playingSize.height / 2;

	for (int i = 0; i < howmany; i++)
	{
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite->setAnchorPoint(Vec2::ZERO); // Vec2::ZERO == Vec2(0,0)
		sprite->setPosition(SpawnX + i * sprite->getContentSize().width, SpawnY);
		nodeItems->addChild(sprite, 0);
	}
	this->addChild(nodeItems, 1);

	//Movable obj
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	
	auto mainSprite = Sprite::create("Blue_Front1.png");
	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(100, (visibleSize.height - playingSize.height));
	mainSprite->setName("mainSprite");
	
	spriteNode->addChild(mainSprite, 1);
	this->addChild(spriteNode, 1);

	////autoMoving the sprite
	//int Destination = 1000;
	//auto moveEvent = MoveBy::create(5, Vec2(Destination, 0));
	//mainSprite->runAction(moveEvent);
	//
	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);

	auto KBlistener = EventListenerKeyboard::create();	
	KBlistener->onKeyPressed  = CC_CALLBACK_2(HelloWorld::onKeyPressed,	 this);
	KBlistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KBlistener, this);

	auto Mlistener = EventListenerMouse::create();
	Mlistener->onMouseMove	 = CC_CALLBACK_1(HelloWorld::onMouseMove,	this);
	Mlistener->onMouseDown	 = CC_CALLBACK_1(HelloWorld::onMouseDown,	this);
	Mlistener->onMouseUp	 = CC_CALLBACK_1(HelloWorld::onMouseUp,		this);
	Mlistener->onMouseScroll = CC_CALLBACK_1(HelloWorld::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mlistener, this);

	this->scheduleUpdate();

	//Class member initializer
	m_moveLeft = false;
	m_moveRight = false;

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
	if (m_moveRight)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(0.0f, Vec2(1.0f, 0.f));
		curSprite->runAction(moveEvent);
	}

	if (m_moveLeft)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(0.0f, Vec2(-1.0f, 0.f));
		curSprite->runAction(moveEvent);
	}

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

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_moveRight = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_moveLeft = true;
	}

}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_moveRight = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_moveLeft = false;
	}

}

void HelloWorld::onMouseMove(cocos2d::Event * event)
{
}

void HelloWorld::onMouseDown(cocos2d::Event * event)
{
}

void HelloWorld::onMouseUp(cocos2d::Event * event)
{
	EventMouse* e = (EventMouse*)event;
	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto stopEvent = curSprite->getActionByTag(1337);
		curSprite->stopAction(stopEvent);

		curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveTo::create(0.5f, Vec2(e->getCursorX(), e->getCursorY()));
		moveEvent->setTag(1337);
		curSprite->runAction(moveEvent);
	}

}

void HelloWorld::onMouseScroll(cocos2d::Event * event)
{
}
