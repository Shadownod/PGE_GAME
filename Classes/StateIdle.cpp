#include "StateIdle.h"
#include "Enemy.h"
StateIdle::StateIdle()
{
}

StateIdle::StateIdle(const string & _stateID, Enemy * _enemyobj)
	: StateBase(_stateID),
	enemyobj(_enemyobj)
{
}

StateIdle::~StateIdle()
{
}


void StateIdle::Enter()
{
	enemyobj->SetMovementSpd(0);
}

void StateIdle::Update()
{
	//Put in alert, if alerted, set next state to chase
	enemyobj->CheckDistance(enemyobj->GetPlayer());
	if (enemyobj->GetAlert())
	{ 
		enemyobj->GetStateMachine()->SetNextState("StateChase");
	}
}

void StateIdle::Exit()
{

}
