#ifndef _STATECHASE_H
#define _STATECHASE_H

#include "StateBase.h"
#include "cocos2d.h"

class StateChase : public StateBase
{
	Enemy* enemyobj;

public:
	StateChase(const String &stateID, Enemy* enemyobj);
	~StateChase();

	void Enter();

	void Update();

	void Exit();
};



#endif