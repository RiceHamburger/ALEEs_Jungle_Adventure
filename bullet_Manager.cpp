#include "bullet_Manager.h"
#include "Level1_Manager.h"
#include "sound.h"

Bullet bullet[BULLET_MAX];
EnemyBullet Enemybullet[ENEMY_BULLET_MAX];
EnemyBullet BossBigbullet[BOSS_BIGBULLET_MAX];

void Bullet_Manager_Init(void) {
	Vector2D pos = { 0.0f, 0.0f };

	//player
	for (int i = 0;i < BULLET_MAX;i++) {
		bullet[i].InitBullet(pos, BULLET);
		bullet[i].SetSpeed(0,0);
		bullet[i].InitSprite();
		bullet[i].SetDamage(BULLET_DAMAGE);
		bullet[i].SetLiveFlag(false);
	}

	//normal bullet
	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		Enemybullet[i].InitBullet(pos, SURAIMUBULLET);
		Enemybullet[i].SetSpeed(0, 0);
		Enemybullet[i].InitSprite();
		Enemybullet[i].SetDamage(ENEMY_BULLET_DAMAGE);
		Enemybullet[i].SetLiveFlag(false);
	}

	//boss big bullet
	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		BossBigbullet[i].InitBullet(pos, BOSS_BIG_BULLET);
		BossBigbullet[i].SetSpeed(0, 0);
		BossBigbullet[i].InitSprite();
		BossBigbullet[i].SetDamage(BOSS_BIGBULLET_DAMAGE);
		BossBigbullet[i].SetLiveFlag(false);
	}
}

void Bullet_Manager_Update(void) {
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
void Bullet_Manager_Draw(void) {

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
void Bullet_Manager_Uninit(void) {
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

void Bullet_Create(float x, float y, float b_x, float b_y) {
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

void EnemyBullet_Create(float x, float y) {
	//fAngle = 0.0f;
	float b_x;
	float b_y;
	Player *p_Player = GetPlayer();
	float fAngle;

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (!Enemybullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_ENEMYSHOT);

			fAngle = GetAngle(x, y, p_Player->GetPosition().x + p_Player->GetWidth()/2, p_Player->GetPosition().y + p_Player->GetHeight() / 2);

			b_x = cosf(fAngle)*5.0f;
			b_y = sinf(fAngle)*5.0f;
			Enemybullet[i].SetPositionX(x);
			Enemybullet[i].SetPositionY(y);
			Enemybullet[i].SetSpeed(b_x, b_y);
			Enemybullet[i].SetLiveFlag(true);
			break;
		}
	}
}

void BossBullet_Create(float x, float y) {
	float b_x;
	float b_y;
	Player *p_Player = GetPlayer();
	float fAngle;

	int bulletCount = 0;

	fAngle = GetAngle(x, y, p_Player->GetPosition().x + p_Player->GetWidth() / 2, p_Player->GetPosition().y + p_Player->GetHeight() / 2);

	float AngleArray[3] = { fAngle ,fAngle + 0.5f,fAngle - 0.5f };

	// one attack creat 3 bullet
	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (!Enemybullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_ENEMYSHOT);

			b_x = cosf(AngleArray[bulletCount]) * 10.0f;
			b_y = sinf(AngleArray[bulletCount]) * 10.0f;
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
void BossBigBullet_Create(float x, float y) {
	float b_x;
	float b_y;
	Player *p_Player = GetPlayer();
	float fAngle;

	fAngle = GetAngle(x, y, p_Player->GetPosition().x + p_Player->GetWidth() / 2, p_Player->GetPosition().y + p_Player->GetHeight() / 2);

	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (!BossBigbullet[i].GetLiveFlag()) {

			//enemy shoot
			PlaySound(SOUND_LABEL_SE_BOSSSHOT);

			b_x = cosf(fAngle) * 5.0f;
			b_y = sinf(fAngle) * 5.0f;
			BossBigbullet[i].SetPositionX(x);
			BossBigbullet[i].SetPositionY(y);
			BossBigbullet[i].SetSpeed(b_x, b_y);
			BossBigbullet[i].SetLiveFlag(true);
			break;
		}
	}
}

bool Bullet_IsEnable(void) {
	for (int i = 0;i < BULLET_MAX;i++) {
		if (bullet[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

bool EnemyBullet_IsEnable(void) {
	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (Enemybullet[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

bool BossBigBullet_IsEnable(void) {
	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (BossBigbullet[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

Bullet *BulletMgrGetBullet() {
	return bullet;
}

EnemyBullet *BulletMgrGetEnemyBullet() {
	return Enemybullet;
}

EnemyBullet *BulletMgrGetBossBigBullet() {
	return BossBigbullet;
}

float GetAngle( float meX, float meY,float targetX, float targetY)
{
	float w = targetX - meX; // cosƒÆ
	float h = targetY - meY; // sinƒÆ

	return atan2f(h, w);
}