#include "StateMachine.h"


StateMachine::StateMachine()
	:m_curr(NULL),
	m_next(NULL)
{

}

StateMachine::~StateMachine()
{
	//for (map<string, StateBase*>::iterator it = m_stateMap.begin(); it != m_stateMap.end(); ++it)
	//{
	//	delete it->second;
	//}
	m_stateVec.clear();
	//m_stateMap.clear();
}


void StateMachine::Update()
{
	if (m_next != m_curr)
	{
		m_curr->Exit();
		m_curr = m_next;
		m_curr->Enter();
	}
	m_curr -> Update();
}

void StateMachine::AddState(StateBase * _newstate)
{
	if (_newstate == nullptr)
	{
		return;
	}

	//for (vector<StateBase*>::iterator it = m_stateVec.begin(); it != m_stateVec.end(); ++it)
	//{
	for(int i = 0 ;i < m_stateVec.size(); ++i)
	{
		if (m_stateVec[i]->GetStateID() == _newstate->GetStateID())
			return;
	}
	
	//if (m_stateMap.find(_newstate->GetStateID()) != m_stateMap.end())
	//	return;
	if (!m_curr)
	{
		m_curr = m_next = _newstate;
	}
	//m_stateMap.insert(_newstate->GetStateID(), _newstate);
	//m_stateMap[_newstate->GetStateID()] = _newstate;
	m_stateVec.push_back(_newstate);
}

void StateMachine::SetNextState(string _nextid)
{
	//map<string, StateBase*>::iterator it = m_stateMap.find(_nextid);
	for (int i = 0; i < m_stateVec.size(); ++i)
	{
		if (m_stateVec[i]->GetStateID() == _nextid)
			m_next = m_stateVec[i];

	}
	//if (it != m_stateMap.end())
	//{
	//	m_next = (StateBase*)it->second;
	//}
}





