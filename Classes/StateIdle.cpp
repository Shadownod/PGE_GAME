#include "StateIdle.h"

StateIdle::StateIdle(const String & _stateID, Enemy * _enemyobj)
	: StateBase(_stateID),
	enemyobj(_enemyobj)
{
}


void StateIdle::Enter()
{
	enemyobj->SetMovementSpd(0);
}

void StateIdle::Update()
{
	//Put in alert, if alerted, set next state to chase
	if (enemyobj->GetAlert())
	{
		enemyobj->GetStateMachine()->SetNextState("State_Chase");
	}
}

void StateIdle::Exit()
{

}
