#include "StateChase.h"
#include "Enemy.h"
#include "Player.h"
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
	enemyobj->SetMovementSpd(50.f);
}

void StateChase::Update()
{
	Vec2 dir(enemyobj->GetPlayer()->GetSprite()->getPosition() - enemyobj->GetSprite()->getPosition());
	dir.normalize();

	enemyobj->GetSprite()->getPhysicsBody()->setVelocity(Vec2(dir.x * enemyobj->GetMovementSpd(), dir.y * enemyobj->GetMovementSpd()));

	//Put in alert, if alerted, set next state to chase
	if (!enemyobj->GetAlert())
	{
		enemyobj->GetStateMachine()->SetNextState("StateIdle"); 
	}
}

void StateChase::Exit()
{

}
