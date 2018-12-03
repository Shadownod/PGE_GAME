#include "StateChase.h"

StateChase::StateChase(const String & _stateID, Enemy * _enemyobj)
	: StateBase(_stateID),
	enemyobj(_enemyobj)
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
