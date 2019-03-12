//==================================================
//  エネミー管理者クラス [EnemyManager.h]        Autor:ロ
//==================================================

#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "enemy.h"
#include "enemy_red.h"

class EnemyManager {
public:
	static void Enemy_Manager_Init(void);
	static void Enemy_Manager_Update(void);
	static void Enemy_Manager_Draw(void);
	static void Enemy_Manager_Uninit(void);

	//Enemy Creat
	static void Enemy_Create(float x, float y);
	static bool Enemy_IsEnable(void);
	static void SetAllEnemyLive(bool flag);

	static Enemy *EnemyMgrGetEnemy();

	//red
	static EnemyRed *EnemyRedMgrGetEnemy();
	static bool EnemyRed_IsEnable();
private:
	static Enemy enemy[ENEMY_MAX];
	static EnemyRed red_enemy;
	static Vector2D enemy_target[ENEMY_MAX][ENEMY_TARGET];
};

#endif