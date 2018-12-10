#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "cocos2d.h"
#include <vector>
USING_NS_CC;

enum MovementDir;

class Projectile
{
public:
	Projectile();
	Projectile(MovementDir _PlayerDir,Vec2 playerPos,Node* spriteNode,float _Speed = 100.0f, float _Damage = 10.0f, float _LifeSpan = 5.0f);

	~Projectile();

	bool onContactBegin(cocos2d::PhysicsContact & contact);


	void SetSpeed(float _Speed);
	void SetDamage(float _Damage);
	void SetLifeSpan(float _LifeSpan);

	float GetSpeed();
	float GetDamage();
	float GetLifeSpan();

	bool GetVisible();

	void ReSpawnBullet(MovementDir _PlayerDir, Vec2 playerPos, Node* spriteNode);
private:
	float Speed;
	float Damage;
	float LifeSpan;
	Sprite* projSprite;
	//PhysicsBody* bulletBody;
};



#endif // !PROJECTILE_H

