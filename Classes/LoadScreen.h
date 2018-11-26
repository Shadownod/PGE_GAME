
#ifndef __LOADSCREEN_H_
#define __LOADSCREEN_H_

#include "cocos2d.h"

class LoadScreen : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(LoadScreen);

	// onKeyPress
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseScroll(cocos2d::Event* event);

	// Physics listener
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	cocos2d::Sprite* getPlayerSprite()
	{
		return mainSprite;
	};

private:
	bool m_moveRight;
	bool m_moveLeft;
	bool m_moveUp;
	bool m_moveDown;

	bool m_animRight;
	bool m_animLeft;
	bool m_animUp;
	bool m_animDown;

	bool m_moveFree;

	cocos2d::Sprite* mainSprite;

	//Animation
	cocos2d::Animate* animateDown;
	cocos2d::Animate* animateRight;
	cocos2d::Animate* animateLeft;
	cocos2d::Animate* animateUp;
};

#endif // _LOADSCENE_H_
