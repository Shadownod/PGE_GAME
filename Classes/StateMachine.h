#pragma once

#include "StateBase.h"
#include "cocos2d.h"
USING_NS_CC;

class StateMachine
{
	StateBase* m_curr;
	StateBase* m_next;
	Map<String, StateBase*>m_stateMap;
	

public:
	StateMachine();
	~StateMachine();

	void Update();

	void AddState(StateBase* _newstate);

	void SetNextState(String _nextid);

	StateBase* GetCurrentState()
	{
		return m_curr;
	}

};