#pragma once

#include "StateBase.h"
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
using std::map;
using std::vector;
USING_NS_CC;
using std::string;
class StateMachine
{

private:
	StateBase *m_curr;
	StateBase *m_next;
	//map<string, StateBase*>m_stateMap;
	vector<StateBase*> m_stateVec;

public:
	StateMachine();
	~StateMachine();

	void Update();

	void AddState(StateBase* _newstate);

	void SetNextState(string _nextid);

	StateBase* GetCurrentState();

};