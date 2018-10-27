#include "enemyBullet.h"


EnemyBullet::EnemyBullet() {
	fAngle = 0.0f;
	distance = ENEMY_BULLET_DISTANCE;
}
EnemyBullet::~EnemyBullet() {

}

void EnemyBullet::BulletActive() {
	Bullet::BulletActive();

	if (GetLiveFlag()) {
		distance--;
		if (distance <= 0) {
			SetLiveFlag(false);
			ResetDis();
		}
	}
	else {
		ResetDis();
	}
	
}

void EnemyBullet::ResetDis() {
	distance = ENEMY_BULLET_DISTANCE;
}