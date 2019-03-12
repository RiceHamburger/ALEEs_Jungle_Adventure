//==================================================
//  弾管理者クラス [BulletManager.cpp]        Autor:ロ
//==================================================

#include "bulletManager.h"
#include "GameScene.h"
#include "sound.h"

// 静的メンバ変数
//==================================================
Bullet BulletManager::bullet[BULLET_MAX];
EnemyBullet BulletManager::Enemybullet[ENEMY_BULLET_MAX];
EnemyBullet BulletManager::BossBigbullet[BOSS_BIGBULLET_MAX];

void BulletManager::Bullet_Manager_Init(void) {
	Vector2D pos = { 0.0f, 0.0f };

	//player
	for (int i = 0;i < BULLET_MAX;i++) {
		bullet[i].InitBullet(pos, BULLET);
		bullet[i].SetSpeed(0, 0);
		bullet[i].InitSprite();
		bullet[i].SetDamage(BULLET_DAMAGE);
		bullet[i].SetLiveFlag(false);

		bullet[i].SetWalkRang(GameScene::GetCanWalkRange());
	}

	//normal bullet
	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		Enemybullet[i].InitBullet(pos, SURAIMUBULLET);
		Enemybullet[i].SetSpeed(0, 0);
		Enemybullet[i].InitSprite();
		Enemybullet[i].SetDamage(ENEMY_BULLET_DAMAGE);
		Enemybullet[i].SetLiveFlag(false);

		Enemybullet[i].SetWalkRang(GameScene::GetCanWalkRange());
	}

	//boss big bullet
	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		BossBigbullet[i].InitBullet(pos, BOSS_BIG_BULLET);
		BossBigbullet[i].SetSpeed(0, 0);
		BossBigbullet[i].InitSprite();
		BossBigbullet[i].SetDamage(BOSS_BIGBULLET_DAMAGE);
		BossBigbullet[i].SetLiveFlag(false);

		BossBigbullet[i].SetWalkRang(GameScene::GetCanWalkRange());
	}
}

void BulletManager::Bullet_Manager_Update(void) {
	for (int i = 0;i < BULLET_MAX;i++) {
		if (bullet[i].GetLiveFlag()) {
			bullet[i].BulletActive();
		}
	}

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (Enemybullet[i].GetLiveFlag()) {
			Enemybullet[i].BulletActive();
		}
	}

	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (BossBigbullet[i].GetLiveFlag()) {
			BossBigbullet[i].BulletActive();
		}
	}
}

void BulletManager::Bullet_Manager_Draw(void) {

	for (int i = 0;i < BULLET_MAX;i++) {
		if (bullet[i].GetLiveFlag()) {
			bullet[i].DrawSprite();
		}
	}

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (Enemybullet[i].GetLiveFlag()) {
			Enemybullet[i].DrawSprite();
		}
	}

	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (BossBigbullet[i].GetLiveFlag()) {
			BossBigbullet[i].DrawSprite();
		}
	}
}

void BulletManager::Bullet_Manager_Uninit(void) {
	for (int i = 0;i < BULLET_MAX;i++) {
		bullet[i].Sprite_Uninit();
	}

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		Enemybullet[i].Sprite_Uninit();
	}

	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		Enemybullet[i].Sprite_Uninit();
	}
}

void BulletManager::Bullet_Create(float x, float y, float b_x, float b_y) {
	for (int i = 0;i < BULLET_MAX;i++) {
		if (!bullet[i].GetLiveFlag()) {
			bullet[i].SetPositionX(x);
			bullet[i].SetPositionY(y);
			bullet[i].SetSpeed(b_x, b_y);
			bullet[i].SetLiveFlag(true);
			break;
		}
	}
}

void BulletManager::EnemyBullet_Create(float x, float y) {
	//fAngle = 0.0f;
	float b_x;
	float b_y;
	Player *p_Player = GameScene::GetPlayer();
	float fAngle;

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (!Enemybullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_ENEMYSHOT);

			fAngle = GetAngle(x, y, p_Player->GetPosition().x + p_Player->GetWidth() / 2, p_Player->GetPosition().y + p_Player->GetHeight() / 2);

			b_x = cosf(fAngle) * ENEMY_BULLET_SPEED;
			b_y = sinf(fAngle) * ENEMY_BULLET_SPEED;
			Enemybullet[i].SetPositionX(x);
			Enemybullet[i].SetPositionY(y);
			Enemybullet[i].SetSpeed(b_x, b_y);
			Enemybullet[i].SetLiveFlag(true);
			break;
		}
	}
}

void BulletManager::BossBullet_Create(float x, float y) {
	float b_x;
	float b_y;
	Player *p_Player = GameScene::GetPlayer();
	float fAngle;

	int bulletCount = 0;

	fAngle = GetAngle(x, y, p_Player->GetPosition().x + p_Player->GetWidth() / 2, p_Player->GetPosition().y + p_Player->GetHeight() / 2);

	float AngleArray[3] = { fAngle ,fAngle + 0.5f,fAngle - 0.5f };

	// one attack creat 3 bullet
	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (!Enemybullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_ENEMYSHOT);

			//*距離
			b_x = cosf(AngleArray[bulletCount]) * BOSS_BULLET_SPEED;
			b_y = sinf(AngleArray[bulletCount]) * BOSS_BULLET_SPEED;
			Enemybullet[i].SetPositionX(x);
			Enemybullet[i].SetPositionY(y);
			Enemybullet[i].SetSpeed(b_x, b_y);
			Enemybullet[i].SetLiveFlag(true);

			bulletCount++;
			if (bulletCount >= 3) {
				break;
			}

		}
	}
}

//big
void BulletManager::BossBigBullet_Create(float x, float y) {
	float b_x;
	float b_y;
	Player *p_Player = GameScene::GetPlayer();
	float fAngle;

	fAngle = GetAngle(x, y, p_Player->GetPosition().x + p_Player->GetWidth() / 2, p_Player->GetPosition().y + p_Player->GetHeight() / 2);

	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (!BossBigbullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_BOSSSHOT);

			b_x = cosf(fAngle) * BOSS_BIG_BULLET_SPEED;
			b_y = sinf(fAngle) * BOSS_BIG_BULLET_SPEED;
			BossBigbullet[i].SetPositionX(x);
			BossBigbullet[i].SetPositionY(y);
			BossBigbullet[i].SetSpeed(b_x, b_y);
			BossBigbullet[i].SetLiveFlag(true);
			break;
		}
	}
}

bool BulletManager::Bullet_IsEnable(void) {
	for (int i = 0;i < BULLET_MAX;i++) {
		if (bullet[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

bool BulletManager::EnemyBullet_IsEnable(void) {
	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (Enemybullet[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

bool BulletManager::BossBigBullet_IsEnable(void) {
	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (BossBigbullet[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

Bullet* BulletManager::BulletMgrGetBullet() {
	return bullet;
}

EnemyBullet* BulletManager::BulletMgrGetEnemyBullet() {
	return Enemybullet;
}

EnemyBullet* BulletManager::BulletMgrGetBossBigBullet() {
	return BossBigbullet;
}

float BulletManager::GetAngle(float meX, float meY, float targetX, float targetY)
{
	float w = targetX - meX; // cosθ
	float h = targetY - meY; // sinθ

	return atan2f(h, w);
}


//red
void BulletManager::EnemyRedBullet_Create(float x, float y, float setAngle) {
	//fAngle = 0.0f;
	float b_x;
	float b_y;
	Player *p_Player = GameScene::GetPlayer();
	float fAngle;

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (!Enemybullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_ENEMYSHOT);

			fAngle = setAngle * PI / 180;

			b_x = cosf(fAngle) * ENEMY_BULLET_SPEED;
			b_y = sinf(fAngle) * ENEMY_BULLET_SPEED;
			Enemybullet[i].SetPositionX(x);
			Enemybullet[i].SetPositionY(y);
			Enemybullet[i].SetSpeed(b_x, b_y);
			Enemybullet[i].SetLiveFlag(true);
			break;
		}
	}
}