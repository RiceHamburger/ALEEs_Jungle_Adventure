#include "EnemyManager.h"

Enemy EnemyManager::enemy[ENEMY_MAX];
EnemyRed EnemyManager::red_enemy;
Vector2D EnemyManager::enemy_target[ENEMY_MAX][ENEMY_TARGET] = {
	{ { 400,28 },{ 900,28 },{ 900,70 },{ 400,70 } },
	{ { 520,265 },{ 778,265 },{ 778,522 },{ 520,522 } },
	{ { 778,522 },{ 520,522 },{ 520,265 },{ 778,265 } },
	{ { 413,785 },{ 413,677 },{ 536,677 },{ 413,503 } },
	{ { 1334,367 },{ 1334,528 },{ 1334,367 },{ 1334,528 } },
	{ { 1468,742 },{ 1468,862 },{ 1134,862 },{ 1134,741 } }
};

void EnemyManager::Enemy_Manager_Init(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		//エネミーのスピードがランダムにする
		float thisEnemySpeed = (float)(rand() % ENEMY_SPEED_MAX) + ENEMY_SPEED_MIN;

		enemy[i].InitEnemy({ 0,0 }, ENEMY, 3, 2);
		enemy[i].SetLife(ENEMY_HEALTHBAR_TOTAL);
		enemy[i].SetScore(ENEMY_SCORE);
		enemy[i].SetSpeed(thisEnemySpeed);
		enemy[i].InitSprite();
		enemy[i].InitBloodSprite();

		for (int j = 0;j < ENEMY_TARGET;j++) {
			enemy[i].SetTargetArr(enemy_target[i][j]);
		}

		enemy[i].SetTargetIndex(1);
		enemy[i].SetPosition(enemy_target[i][0]);
	}


	//red
	red_enemy.InitEnemy({ 1700,245 }, ENEMY_RED, 3, 2);
	red_enemy.SetLife(ENEMY_HEALTHBAR_TOTAL);
	red_enemy.SetScore(ENEMY_SCORE);
	red_enemy.InitSprite();
	red_enemy.InitBloodSprite();
	red_enemy.SetLiveFlag(true);
}

void EnemyManager::Enemy_Manager_Update(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].EnemyActive();
		}
		else {
			enemy[i].EnemyRespawn();
		}
	}

	//red
	red_enemy.EnemyActive();
}

void EnemyManager::Enemy_Manager_Draw(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].DrawSprite(enemy[i].GetRect());
			enemy[i].DrawBloodSprite();
		}
	}

	//red
	if (red_enemy.GetLiveFlag()) {
		red_enemy.DrawSprite(red_enemy.GetRect());
		red_enemy.DrawBloodSprite();
	}
}

void EnemyManager::Enemy_Manager_Uninit(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].SetLiveFlag(false);
		}
		enemy[i].Sprite_Uninit();
		enemy[i].BloodSprite_Uninit();
		enemy[i].DeletTargetArr();
	}

	//red
	red_enemy.Sprite_Uninit();
	red_enemy.BloodSprite_Uninit();
}

void EnemyManager::Enemy_Create(float x, float y) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (!enemy[i].GetLiveFlag()) {
			enemy[i].SetPositionX(x);
			enemy[i].SetPositionY(y);
			enemy[i].SetLiveFlag(true);
			break;
		}
	}
}

bool EnemyManager::Enemy_IsEnable(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

bool EnemyManager::EnemyRed_IsEnable(void) {
	if (red_enemy.GetLiveFlag()) {
		return true;
	}
	return false;
}

Enemy* EnemyManager::EnemyMgrGetEnemy() {
	return enemy;
}

EnemyRed* EnemyManager::EnemyRedMgrGetEnemy() {
	return &red_enemy;
}

void EnemyManager::SetAllEnemyLive(bool flag) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].SetLiveFlag(flag);
		}
	}

	//red
	red_enemy.SetLiveFlag(flag);
}