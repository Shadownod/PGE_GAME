#include "StateChase.h"
#include "Enemy.h"
StateChase::StateChase()
{
}

StateChase::StateChase(const string & _stateID, Enemy * _enemyobj)
	: StateBase(_stateID),
	enemyobj(_enemyobj)
{
}

StateChase::~StateChase()
{
}


void StateChase::Enter()
{
	enemyobj->SetMovementSpd(0);
}

void StateChase::Update()
{
	//Put in alert, if alerted, set next state to chase
	if (!enemyobj->GetAlert())
	{
		enemyobj->GetStateMachine()->SetNextState("State_Idle");
	}
}

void StateChase::Exit()
{

}
