#ifndef _STATECHASE_H
#define _STATECHASE_H

#include "StateBase.h"
#include "cocos2d.h"
class Enemy;
class StateChase : public StateBase
{
	Enemy* enemyobj;

public:
	StateChase();
	StateChase(const string &stateID, Enemy* enemyobj);
	~StateChase();

	void Enter();

	void Update();

	void Exit();
};



#endif