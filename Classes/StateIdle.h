#ifndef _STATEIDLE_H
#define _STATEIDLE_H

#include "StateBase.h"
#include "cocos2d.h"

class StateIdle : public StateBase
{
	Enemy* enemyobj;

public:
	StateIdle(const String &stateID, Enemy* enemyobj);
	~StateIdle();

	void Enter();

	void Update();

	void Exit();
};



#endif