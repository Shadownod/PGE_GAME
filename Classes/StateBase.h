
#ifndef _STATEBASE_H
#define _STATEBASE_H

#include "Enemy.h"

class StateBase
{

public:

	StateBase(const String &stateID);
	~StateBase();


	virtual void Enter() = 0;

	virtual void Update() = 0;

	virtual void Exit() = 0;

	const String& GetStateID()
	{
		return StateId;
	};

	String StateId;

};



#endif