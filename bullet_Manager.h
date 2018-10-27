#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#define PI 3.14159265

#include "bullet.h"
#include "enemyBullet.h"

void Bullet_Manager_Init(void);
void Bullet_Manager_Update(void);
void Bullet_Manager_Draw(void);
void Bullet_Manager_Uninit(void);

bool Bullet_IsEnable(void);
bool EnemyBullet_IsEnable(void);
bool BossBigBullet_IsEnable(void);
void Bullet_Create(float x, float y,float b_x,float b_y);
void EnemyBullet_Create(float x, float y);
void BossBullet_Create(float x, float y);
void BossBigBullet_Create(float x, float y);

Bullet *BulletMgrGetBullet();
EnemyBullet *BulletMgrGetEnemyBullet();
EnemyBullet *BulletMgrGetBossBigBullet();

float GetAngle(float meX, float meY, float targetX, float targetY);

#endif