#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "enemy.h"

void Enemy_Manager_Init(void);
void Enemy_Manager_Update(void);
void Enemy_Manager_Draw(void);
void Enemy_Manager_Uninit(void);

//Enemy Creat
void Enemy_Create(float x, float y);
bool Enemy_IsEnable(void);
void SetAllEnemyLive(bool flag);

Enemy *EnemyMgrGetEnemy();

#endif