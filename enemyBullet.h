#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "texture.h"
#include "bullet.h"

#define ENEMY_BULLET_MAX (40)
#define BOSS_BIGBULLET_MAX (5)
#define ENEMY_BULLET_WIDTH (64)
#define ENEMY_BULLET_DISTANCE (1000)
#define ENEMY_BULLET_SPEED (0.6f)
#define BOSS_BULLET_SPEED (1)
#define BOSS_BIG_BULLET_SPEED (0.5f)

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