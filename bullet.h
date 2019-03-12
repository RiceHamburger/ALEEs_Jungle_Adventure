#ifndef BULLET_H_
#define BULLET_H_

#include "texture.h"
#include "object.h"

#define BULLET_MAX (100)
#define ENEMY_BULLET_MAX (30)
#define BULLET_WIDTH (16)

#define BULLET_DAMAGE (1)
#define ENEMY_BULLET_DAMAGE (10)
#define BOSS_BIGBULLET_DAMAGE (20)

class Bullet :public Object {
protected:
	float speedX;
	float speedY;
	int bulletDamage;

	//�ړ��͈͂̌���
	int* MoveRank;
public:
	Bullet();
	~Bullet();
	void InitBullet(Vector2D pos, TEXTURE_NAME tex_name);
	void BulletActive();
	void BulletDestroy();

	void SetSpeed(float Speedx, float Speedy);

	void SetDamage(int hit);
	int GetDamage();
	//float GetSpeed();

	//�͈̓Z�b�g
	void SetWalkRang(int* rang);
	//�͈̓`�F�b�N
	bool RangCheck(float x, float y);
};

#endif //BULLET_H_