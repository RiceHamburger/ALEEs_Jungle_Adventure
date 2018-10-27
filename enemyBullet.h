#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "texture.h"
#include "bullet.h"

#define ENEMY_BULLET_MAX (40)
#define BOSS_BIGBULLET_MAX (5)
#define ENEMY_BULLET_WIDTH (64)
#define ENEMY_BULLET_DISTANCE (100)

class EnemyBullet :public Bullet {
private:
	float fAngle;
	int distance;
public:
	EnemyBullet();
	~EnemyBullet();
	void BulletActive();
	void ResetDis();
};

#endif //ENEMYBULLET_H_