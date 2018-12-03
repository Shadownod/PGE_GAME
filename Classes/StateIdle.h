#ifndef _STATEIDLE_H
#define _STATEIDLE_H

#include "StateBase.h"
#include "cocos2d.h"
#include <string>
using std::string;
class Enemy;
class StateIdle : public StateBase
{
	Enemy* enemyobj;

public:
	StateIdle();
	StateIdle(const string &stateID, Enemy* enemyobj);
	~StateIdle();

	void Enter();

	void Update();

	void Exit();
};



#endif