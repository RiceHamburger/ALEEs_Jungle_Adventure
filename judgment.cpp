#include "judgment.h"
#include "bullet_Manager.h"
#include "enemy_Manager.h"
#include "explosion_Manager.h"
#include "Level1_Manager.h"
#include "tree_Manager.h"
#include "sound.h"

static RECT endArea = { 2283,449,2424,510 };

bool Collision_HitCircle(const Circle* p_Circle_a, const Circle* p_Circle_b) {
	float L_dis = p_Circle_a->r + p_Circle_b->r;

	float C_c = (p_Circle_a->cx - p_Circle_b->cx) * (p_Circle_a->cx - p_Circle_b->cx) + (p_Circle_a->cy - p_Circle_b->cy) * (p_Circle_a->cy - p_Circle_b->cy);

	return C_c < L_dis * L_dis;
}

void Judgment_Bullet_vs_Enemy(void) {
	//弾とエネミーは有効か？
	if (!Enemy_IsEnable() || !Bullet_IsEnable()) {
		return;
	}

	Bullet *Bullets = BulletMgrGetBullet();
	Enemy *Enemys = EnemyMgrGetEnemy();
	Player *p_Player = GetPlayer();
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
							Explosion_Create(Enemys[j].GetPosition().x - Enemys[j].GetWidth() / 2, Enemys[j].GetPosition().y - Enemys[j].GetHeight() / 2);
							p_Player->AddScore(Enemys[j].GetScore() * 20);
						}
						
					}
				}
			}
		}
	}

}

void Judgment_Bullet_vs_Player(void) {
	Player *p_Player = GetPlayer();

	if (!EnemyBullet_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	EnemyBullet *Bullets = BulletMgrGetEnemyBullet();
	

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
					LevelClear();
				}
			}
		}
	}
}

void Judgment_Player_vs_Enemy(void) {
	Player *p_Player = GetPlayer();
	if (!Enemy_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	Enemy *Enemys = EnemyMgrGetEnemy();
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

					LevelClear();
				}
			}
		}
	}
}

int Collision(RECT rect1, RECT rect2)
{
	RECT dest;
	return IntersectRect(&dest, &rect1, &rect2);
}

bool Judgment_Player_vs_Tree(D3DXVECTOR2 vec) {

	D3DXVECTOR2 vecS = vec;

	Player *p_Player = GetPlayer();
	RECT *Trees_Collsion = GetTree();
	RECT player_rect;
	player_rect.left = p_Player->GetPosition().x;
	player_rect.top = p_Player->GetPosition().y;
	player_rect.right = player_rect.left + p_Player->GetWidth();
	player_rect.bottom = player_rect.top + p_Player->GetHeight();


	RECT dest;
	for (int i = 0;i < TREE_COLLSION_MAX;i++) {
		if (IntersectRect(&dest,&player_rect, &Trees_Collsion[i])) {

			//left
			if (dest.right == player_rect.right) {
				if (player_rect.right > Trees_Collsion[i].left) {
					p_Player->SetPositionX(Trees_Collsion[i].left - p_Player->GetWidth());
				}
			}

			//right
			if (dest.left == player_rect.left) {
				if (player_rect.left < Trees_Collsion[i].right) {
					p_Player->SetPositionX(Trees_Collsion[i].right);
				}
			}

			//top
			if (dest.bottom == player_rect.bottom) {
				if (player_rect.bottom > Trees_Collsion[i].top) {
					p_Player->SetPositionY(Trees_Collsion[i].top - p_Player->GetHeight());
				}
			}

			
			//bottom
			if (dest.top == player_rect.top) {
				if (player_rect.top < Trees_Collsion[i].bottom) {
					p_Player->SetPositionY(Trees_Collsion[i].bottom);
				}
			}
			break;
			//return true;
		}
	}
	return false;
}

void StartShowBoss(void) {
	Player *p_Player = GetPlayer();

	RECT player_rect;
	player_rect.left = p_Player->GetPosition().x;
	player_rect.top = p_Player->GetPosition().y;
	player_rect.right = p_Player->GetPosition().x + p_Player->GetWidth();
	player_rect.bottom = p_Player->GetPosition().y + p_Player->GetHeight();

	RECT area;
	if (IntersectRect(&area, &player_rect, &endArea)) {
		CameraCancelFollow();
	}
}

void Judgment_Bullet_vs_Boss(void) {
	Boss *p_boss = GetBoss();
	if (!p_boss->GetActiveflag() || !Bullet_IsEnable()) {
		return;
	}

	Bullet *Bullets = BulletMgrGetBullet();
	Player *p_Player = GetPlayer();
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
					LevelClear();
					
				}

			}
		}
	}
}

void Judgment_Player_vs_Boss(void) {
	Player *p_Player = GetPlayer();
	Boss *p_boss = GetBoss();
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

			LevelClear();
		}
	}
}

//boss big bullet
void Judgment_BigBullet_vs_Player(void) {
	Boss *p_boss = GetBoss();
	Player *p_Player = GetPlayer();
	if (!p_boss->GetActiveflag() || !BossBigBullet_IsEnable() || p_Player->GetInvincible()) {
		return;
	}

	EnemyBullet *Bullets = BulletMgrGetBossBigBullet();


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
					LevelClear();
				}
			}
		}
	}
}