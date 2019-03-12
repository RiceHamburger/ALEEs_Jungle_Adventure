//==================================================
//  íeä«óùé“ÉNÉâÉX [BulletManager.h]        Autor:Éç
//==================================================

#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "bullet.h"
#include "enemyBullet.h"

#define PI 3.14159265

class BulletManager {
public:
	static void Bullet_Manager_Init(void);
	static void Bullet_Manager_Update(void);
	static void Bullet_Manager_Draw(void);
	static void Bullet_Manager_Uninit(void);

	static bool Bullet_IsEnable(void);
	static bool EnemyBullet_IsEnable(void);
	static bool BossBigBullet_IsEnable(void);
	static void Bullet_Create(float x, float y, float b_x, float b_y);
	static void EnemyBullet_Create(float x, float y);
	static void BossBullet_Create(float x, float y);
	static void BossBigBullet_Create(float x, float y);

	static Bullet *BulletMgrGetBullet();
	static EnemyBullet *BulletMgrGetEnemyBullet();
	static EnemyBullet *BulletMgrGetBossBigBullet();

	static float GetAngle(float meX, float meY, float targetX, float targetY);

	//red
	static void EnemyRedBullet_Create(float x, float y, float setAngle);
private:
	static Bullet bullet[BULLET_MAX];
	static EnemyBullet Enemybullet[ENEMY_BULLET_MAX];
	static EnemyBullet BossBigbullet[BOSS_BIGBULLET_MAX];
};


#endif