#include "StateMachine.h"

StateMachine::StateMachine()
	:m_curr(NULL),
	m_next(NULL)
{

}

StateMachine::~StateMachine()
{
	for (Map<String, StateBase*>::iterator it = m_stateMap.begin(); it != m_stateMap.end(); ++it)
	{
		delete it->second;
	}
	m_stateMap.clear();
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
	if (m_stateMap.find(_newstate->GetStateID()) != m_stateMap.end())
		return;
	if (!m_curr)
	{
		m_curr = m_next = _newstate;
	}
	m_stateMap.insert(_newstate->GetStateID(), _newstate);
}

void StateMachine::SetNextState(String _nextid)
{
	Map<String, StateBase*>::iterator it = m_stateMap.find(_nextid);
	if (it != m_stateMap.end())
	{
		m_next = (StateBase*)it->second;
	}
}





