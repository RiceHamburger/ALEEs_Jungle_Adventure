//==================================================
//  裁きのクラス [Judgment.cpp]        Autor:ロ
//==================================================
#include <stdlib.h>
#include "judgment.h"
#include "bulletManager.h"
#include "EnemyManager.h"
#include "ExplosionManager.h"
#include "GameScene.h"
//#include "tree_Manager.h"
#include "sound.h"
#include "TonicManager.h"

//BOSS戦開始エリア
RECT Judgment::endArea = { 2283,449,2424,510 };

//円の当たり判定処理
//==================================================
bool Judgment::Collision_HitCircle(const Circle* p_Circle_a, const Circle* p_Circle_b) {
	float L_dis = p_Circle_a->r + p_Circle_b->r;

	float C_c = (p_Circle_a->cx - p_Circle_b->cx) * (p_Circle_a->cx - p_Circle_b->cx) + (p_Circle_a->cy - p_Circle_b->cy) * (p_Circle_a->cy - p_Circle_b->cy);

	return C_c < L_dis * L_dis;
}

//弾とエネミーの判定処理
//==================================================
void Judgment::Judgment_Bullet_vs_Enemy(void) {
	//弾とエネミーは有効か？
	if (!EnemyManager::Enemy_IsEnable() || !BulletManager::Bullet_IsEnable()) {
		return;
	}

	Bullet *Bullets = BulletManager::BulletMgrGetBullet();
	Enemy *Enemys = EnemyManager::EnemyMgrGetEnemy();
	Player *p_Player = GameScene::GetPlayer();
	//弾のコリジョンとエネミーのコリジョン
	for (int i = 0;i < BULLET_MAX;i++) {
		if (Bullets[i].GetLiveFlag()) {
			for (int j = 0;j < ENEMY_MAX;j++) {
				if (Enemys[j].GetLiveFlag()) {
					if (Collision_HitCircle(Bullets[i].GetCircleCollision(), Enemys[j].GetCircleCollision())) {
						//当たってる
						Bullets[i].BulletDestroy();

						PlaySound(SOUND_LABEL_SE_ENEMYHITED);

						//enemy effect
						Enemys[j].SetDamageEffect(true);

						if (Enemys[j].GetLife() >= 2) {
							Enemys[j].SetLife(Enemys[j].GetLife() - Bullets[i].GetDamage());
							p_Player->AddScore(Enemys[j].GetScore());
						}
						else {
							//enemy destroy
							PlaySound(SOUND_LABEL_SE_EXPLOSION);
							Enemys[j].EnemyDestroy();
							ExplosionManager::Explosion_Create(Enemys[j].GetPosition().x - Enemys[j].GetWidth() / 2, Enemys[j].GetPosition().y - Enemys[j].GetHeight() / 2);
							
							//乱数でアイテムを出す
							int min = 1;
							int max = 10;
							int seed = rand() % (max - min + 1) + min;
							if (seed <= 5) {
								TonicManager::Tonic_Create(Enemys[j].GetPosition().x + Enemys[j].GetWidth() / 2, Enemys[j].GetPosition().y + Enemys[j].GetHeight() / 2);
							}

							p_Player->AddScore(Enemys[j].GetScore() * 20);
						}
						
					}
				}
			}
		}
	}

}

//弾とエネミーの判定処理
//==================================================
void Judgment::Judgment_Bullet_vs_Player(void) {
	Player *p_Player = GameScene::GetPlayer();

	if (!BulletManager::EnemyBullet_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	EnemyBullet *Bullets = BulletManager::BulletMgrGetEnemyBullet();
	

	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (Bullets[i].GetLiveFlag()) {
			if (Collision_HitCircle(Bullets[i].GetCircleCollision(), p_Player->GetCircleCollision())) {
				//当たってる
				Bullets[i].BulletDestroy();
				Bullets[i].ResetDis();

				PlaySound(SOUND_LABEL_SE_PLAYERHITED);

				if (p_Player->GetLife() > 0) {
					p_Player->SetLife(p_Player->GetLife() - Bullets[i].GetDamage());
					p_Player->SetInvincible(true);
				}
				else {
					PlaySound(SOUND_LABEL_SE_PLAYERDIE);
					GameScene::LevelClear();
				}
			}
		}
	}
}

//プレーヤーとエネミーの判定処理
//==================================================
void Judgment::Judgment_Player_vs_Enemy(void) {
	Player *p_Player = GameScene::GetPlayer();
	if (!EnemyManager::Enemy_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	Enemy *Enemys = EnemyManager::EnemyMgrGetEnemy();
	for (int j = 0;j < ENEMY_MAX;j++) {
		if (Enemys[j].GetLiveFlag()) {

			//player hit enemy
			if (Collision_HitCircle(p_Player->GetCircleCollision(), Enemys[j].GetCircleCollision())) {

				//当たってる
				if (p_Player->GetLife() > 0) {
					p_Player->SetLife(p_Player->GetLife() - Enemys[j].GetEnemyBodyDamage());
					p_Player->SetInvincible(true);

					PlaySound(SOUND_LABEL_SE_PLAYERHITED);

					//return
					if (Enemys[j].GetPosition().x > p_Player->GetPosition().x) {
						p_Player->SetMoveX(-20);
					}

					if (Enemys[j].GetPosition().x < p_Player->GetPosition().x) {
						p_Player->SetMoveX(20);
					}

					if (Enemys[j].GetPosition().y > p_Player->GetPosition().y) {
						p_Player->SetMoveY(-20);
					}

					if (Enemys[j].GetPosition().y < p_Player->GetPosition().y) {
						p_Player->SetMoveX(20);
					}
				}
				else {
					PlaySound(SOUND_LABEL_SE_PLAYERDIE);

					GameScene::LevelClear();
				}
			}
		}
	}
}

//BOSS表示処理
//==================================================
void Judgment::StartShowBoss(void) {
	Player *p_Player = GameScene::GetPlayer();

	RECT player_rect;
	player_rect.left = p_Player->GetPosition().x;
	player_rect.top = p_Player->GetPosition().y;
	player_rect.right = p_Player->GetPosition().x + p_Player->GetWidth();
	player_rect.bottom = p_Player->GetPosition().y + p_Player->GetHeight();

	RECT area;
	if (IntersectRect(&area, &player_rect, &endArea)) {
		GameScene::CameraCancelFollow();
	}
}

//弾とBOSSの判定処理
//==================================================
void Judgment::Judgment_Bullet_vs_Boss(void) {
	Boss *p_boss = GameScene::GetBoss();
	if (!p_boss->GetActiveflag() || !BulletManager::Bullet_IsEnable()) {
		return;
	}

	Bullet *Bullets = BulletManager::BulletMgrGetBullet();
	Player *p_Player = GameScene::GetPlayer();
	//弾のコリジョンとエネミーのコリジョン
	for (int i = 0;i < BULLET_MAX;i++) {
		if (Bullets[i].GetLiveFlag()) {
			if (Collision_HitCircle(Bullets[i].GetCircleCollision(), p_boss->GetCircleCollision())) {
				//当たってる
				Bullets[i].BulletDestroy();

				PlaySound(SOUND_LABEL_SE_ENEMYHITED);

				//enemy effect
				p_boss->SetDamageEffect(true);

				if (p_boss->GetLife() >= 2) {
					p_boss->SetLife(p_boss->GetLife() - Bullets[i].GetDamage());
					p_Player->AddScore(p_boss->GetScore());
				}
				else {
					//boss destroy
					PlaySound(SOUND_LABEL_SE_BOSSDIE);
					p_boss->SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 127));
					p_Player->AddScore(p_boss->GetScore() * 100);
					GameScene::LevelClear();
					
				}

			}
		}
	}
}

//プレーヤーとBOSSの判定処理
//==================================================
void Judgment::Judgment_Player_vs_Boss(void) {
	Player *p_Player = GameScene::GetPlayer();
	Boss *p_boss = GameScene::GetBoss();
	if (!p_boss->GetActiveflag() || p_Player->GetInvincible()) {
		return;
	}

	//player hit enemy
	if (Collision_HitCircle(p_Player->GetCircleCollision(), p_boss->GetCircleCollision())) {

		//当たってる
		if (p_Player->GetLife() > 0) {
			p_Player->SetLife(p_Player->GetLife() - p_boss->GetEnemyBodyDamage());
			p_Player->SetInvincible(true);

			PlaySound(SOUND_LABEL_SE_PLAYERHITED);

			//return
			if (p_boss->GetPosition().x > p_Player->GetPosition().x) {
				p_Player->SetMoveX(-20);
			}

			if (p_boss->GetPosition().x < p_Player->GetPosition().x) {
				p_Player->SetMoveX(20);
			}

			if (p_boss->GetPosition().y > p_Player->GetPosition().y) {
				p_Player->SetMoveY(-20);
			}

			if (p_boss->GetPosition().y < p_Player->GetPosition().y) {
				p_Player->SetMoveX(20);
			}
		}
		else {
			PlaySound(SOUND_LABEL_SE_PLAYERDIE);

			GameScene::LevelClear();
		}
	}
}

//大きい弾とプレーヤーの判定処理
//==================================================
void Judgment::Judgment_BigBullet_vs_Player(void) {
	Boss *p_boss = GameScene::GetBoss();
	Player *p_Player = GameScene::GetPlayer();
	if (!p_boss->GetActiveflag() || !BulletManager::BossBigBullet_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	EnemyBullet *Bullets = BulletManager::BulletMgrGetBossBigBullet();


	for (int i = 0;i < BOSS_BIGBULLET_MAX;i++) {
		if (Bullets[i].GetLiveFlag()) {
			if (Collision_HitCircle(Bullets[i].GetCircleCollision(), p_Player->GetCircleCollision())) {
				//当たってる
				Bullets[i].BulletDestroy();
				Bullets[i].ResetDis();

				PlaySound(SOUND_LABEL_SE_PLAYERHITED);

				if (p_Player->GetLife() > 0) {
					p_Player->SetLife(p_Player->GetLife() - Bullets[i].GetDamage());
					p_Player->SetInvincible(true);
				}
				else {
					PlaySound(SOUND_LABEL_SE_PLAYERDIE);
					GameScene::LevelClear();
				}
			}
		}
	}
}

//アイテムとプレーヤーの判定処理
//==================================================
void Judgment::Judgment_Tonic_vs_Player(void) {
	Player *p_Player = GameScene::GetPlayer();

	if (!TonicManager::Tonic_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	Tonic *Tonics = TonicManager::TonicMgrGetTonic();


	for (int i = 0;i < ENEMY_BULLET_MAX;i++) {
		if (Tonics[i].GetLiveFlag()) {
			if (Collision_HitCircle(Tonics[i].GetCircleCollision(), p_Player->GetCircleCollision())) {

				PlaySound(SOUND_LABEL_SE_ITEM);

				//当たってる
				//1.hp up
				switch (Tonics[i].GetState())
				{
				case HPUP:
					
					p_Player->SetLife(p_Player->GetLife() + Tonics[i].GetAddHealth());

					if (p_Player->GetLife() > 200) {
						p_Player->SetLife(200);
					}
					break;
				case SHOOTGUN:
					p_Player->SetItemCheck(true);
					break;
				}
				
				Tonics[i].TonicDestroy();
			}
		}
	}
}

//弾と赤いエネミーの判定処理
//==================================================
void Judgment::Judgment_Bullet_vs_EnemyRed(void) {
	//弾とエネミーは有効か？
	if (!EnemyManager::EnemyRed_IsEnable() || !BulletManager::Bullet_IsEnable()) {
		return;
	}

	Bullet *Bullets = BulletManager::BulletMgrGetBullet();
	EnemyRed *Enemys = EnemyManager::EnemyRedMgrGetEnemy();
	Player *p_Player = GameScene::GetPlayer();

	//弾のコリジョンとエネミーのコリジョン
	for (int i = 0;i < BULLET_MAX;i++) {
		if (Bullets[i].GetLiveFlag()) {
				if (Enemys->GetLiveFlag()) {
					if (Collision_HitCircle(Bullets[i].GetCircleCollision(), Enemys->GetCircleCollision())) {
						//当たってる
						Bullets[i].BulletDestroy();

						PlaySound(SOUND_LABEL_SE_ENEMYHITED);

						//enemy effect
						Enemys->SetDamageEffect(true);

						if (Enemys->GetLife() >= 2) {
							Enemys->SetLife(Enemys->GetLife() - Bullets[i].GetDamage());
							p_Player->AddScore(Enemys->GetScore());
						}
						else {
							//enemy destroy
							PlaySound(SOUND_LABEL_SE_EXPLOSION);
							Enemys->EnemyDestroy();
							ExplosionManager::Explosion_Create(Enemys->GetPosition().x - Enemys->GetWidth() / 2, Enemys->GetPosition().y - Enemys->GetHeight() / 2);

							//アイテムを出す
							TonicManager::Tonic_CreateGun(Enemys->GetPosition().x + Enemys->GetWidth() / 2, Enemys->GetPosition().y + Enemys->GetHeight() / 2);
							
							p_Player->AddScore(Enemys->GetScore() * 20);
						}

					}
				}
			
		}
	}

}

//プレーヤーと赤いエネミーの判定処理
//==================================================
void Judgment::Judgment_Player_vs_EnemyRed(void) {
	Player *p_Player = GameScene::GetPlayer();
	if (!EnemyManager::EnemyRed_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	EnemyRed *Enemys = EnemyManager::EnemyRedMgrGetEnemy();

			//player hit enemy
			if (Collision_HitCircle(p_Player->GetCircleCollision(), Enemys->GetCircleCollision())) {

				//当たってる
				if (p_Player->GetLife() > 0) {
					p_Player->SetLife(p_Player->GetLife() - Enemys->GetEnemyBodyDamage());
					p_Player->SetInvincible(true);

					PlaySound(SOUND_LABEL_SE_PLAYERHITED);

					//return
					/*if (Enemys->GetPosition().x > p_Player->GetPosition().x) {
						p_Player->SetMoveX(-20);
					}

					if (Enemys->GetPosition().x < p_Player->GetPosition().x) {
						p_Player->SetMoveX(20);
					}

					if (Enemys[j].GetPosition().y > p_Player->GetPosition().y) {
						p_Player->SetMoveY(-20);
					}

					if (Enemys[j].GetPosition().y < p_Player->GetPosition().y) {
						p_Player->SetMoveX(20);
					}*/
					p_Player->SetMoveY(40);
				}
				else {
					PlaySound(SOUND_LABEL_SE_PLAYERDIE);

					GameScene::LevelClear();
				}
			}
		
}

//プレーヤーと赤いエネミー可視範囲の判定処理
//==================================================
void Judgment::Judgment_Player_vs_EnemyRedRange(void) {

	EnemyRed *Enemys = EnemyManager::EnemyRedMgrGetEnemy();
	if (!Enemys->GetLiveFlag())return;

	Player *p_Player = GameScene::GetPlayer();
	//player hit enemy
	if (Collision_HitCircle(p_Player->GetCircleCollision(), Enemys->GetSeeCircleCollision())) {

		Enemys->EnemyAttack();
	}
	else {
		Enemys->AngleReset();
	}

}