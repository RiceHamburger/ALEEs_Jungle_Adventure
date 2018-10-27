#include "enemy_Manager.h"

Enemy enemy[ENEMY_MAX];
Vector2D enemy_target[ENEMY_MAX][ENEMY_TARGET] = {
	{ {400,28},{900,28},{ 900,70 },{ 400,70 }},
	{ { 520,265 },{ 778,265 },{ 778,522 },{ 520,522 } },
	{ { 778,522 },{ 520,522 },{ 520,265 },{ 778,265 } },
	{ { 413,785 },{ 413,677 },{ 536,677 },{ 413,503 } },
	{ { 1334,367 },{ 1334,528 },{ 1334,367 },{ 1334,528 } },
	{ { 1468,742 },{ 1468,862 },{ 1134,862 },{ 1134,741 } }
};

void Enemy_Manager_Init(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		//エネミーのスピードがランダムにする
		float thisEnemySpeed = (float)(rand() % ENEMY_SPEED_MAX) + ENEMY_SPEED_MIN;

		enemy[i].InitEnemy({0,0}, ENEMY, 3, 2);
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
}

void Enemy_Manager_Update(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].EnemyActive();
		}
		else {
			enemy[i].EnemyRespawn();
		}
	}

	//このレベルの動き
	/*if (!Enemy_IsEnable()) {
		Enemy_Create(SCREEN_WIDTH, (rand() % SCREEN_HEIGHT - 100));
	}*/
}

void Enemy_Manager_Draw(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].DrawSprite(enemy[i].GetRect());
			enemy[i].DrawBloodSprite();
		}
	}
}

void Enemy_Manager_Uninit(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].SetLiveFlag(false);
		}
		enemy[i].Sprite_Uninit();
		enemy[i].BloodSprite_Uninit();
		enemy[i].DeletTargetArr();
	}
}

void Enemy_Create(float x, float y) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (!enemy[i].GetLiveFlag()) {
			enemy[i].SetPositionX(x);
			enemy[i].SetPositionY(y);
			enemy[i].SetLiveFlag(true);
			break;
		}
	}
}

bool Enemy_IsEnable(void) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

Enemy *EnemyMgrGetEnemy() {
	return enemy;
}

void SetAllEnemyLive(bool flag) {
	for (int i = 0;i < ENEMY_MAX;i++) {
		if (enemy[i].GetLiveFlag()) {
			enemy[i].SetLiveFlag(flag);
		}
	}
}