#include "enemyBullet.h"

//コンストラクタ
//==================================================
EnemyBullet::EnemyBullet() {
	fAngle = 0.0f;
	distance = ENEMY_BULLET_DISTANCE;
}

//デストラクタ
//==================================================
EnemyBullet::~EnemyBullet() {

}

//更新処理
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

//弾の移動範囲更新処理
//==================================================
void EnemyBullet::ResetDis() {
	distance = ENEMY_BULLET_DISTANCE;
}