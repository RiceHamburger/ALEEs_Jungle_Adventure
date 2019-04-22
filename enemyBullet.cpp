#include "enemyBullet.h"

//�R���X�g���N�^
//==================================================
EnemyBullet::EnemyBullet() {
	fAngle = 0.0f;
	distance = ENEMY_BULLET_DISTANCE;
}

//�f�X�g���N�^
//==================================================
EnemyBullet::~EnemyBullet() {

}

//�X�V����
//==================================================
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

//�e�̈ړ��͈͍X�V����
//==================================================
void EnemyBullet::ResetDis() {
	distance = ENEMY_BULLET_DISTANCE;
}