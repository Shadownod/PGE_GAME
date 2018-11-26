#pragma once
#include "StateBase.h"


class StateWander : StateBase
{
public:
	StateWander();
	~StateWander();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();
};