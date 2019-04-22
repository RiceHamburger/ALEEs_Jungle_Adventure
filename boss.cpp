#include "boss.h"
#include "D3Dsetup.h"
#include "bulletManager.h"

// 初期化処理
//==================================================
void Boss::Init(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(BOSS_WIDTH);
	SetHeight(BOSS_HEIGHT);

	//state
	state = BossState_Show;
	targetIndex = 0;
	SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));

	//判定の円を設定する
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + BOSS_Y;
	objCollision.r = GetWidth()*0.47f;

	SetCircleCollision(objCollision);

	this->SetLiveFlag(true);
	bossActiv = false;

	bodydamage = BOSS_BODYDAMAGE;

	//sprite rect
	textureX = 0;
	textureY = 0;
	textureX_index = 0;
	textureY_index = 0;
	textureX_NUM = tex_pic_numX;
	textureY_NUM = tex_pic_numY;
	aniTime = BOSS_ANIMATION_TIME;
	text_rec.left = textureX;
	text_rec.top = textureY;
	text_rec.right = text_rec.left + GetHeight();
	text_rec.bottom = text_rec.top + GetHeight();

	//hp bar
	oldHealth = BOSS_HEALTHBAR_TOTAL;
	health_percent = 1.0f;

	//attack time
	attackTime = BOSS_ATTACK_TIME;
	BigattackTime = BOSS_BIGATTACK_TIME_MAX;
	Effect = false;
	Effect_time = BOSS_EFFECT_TIME;

	//boss active count
	activeCount = 0;
}

//更新処理
//==================================================
void Boss::Active() {
	Vector2D position = GetPosition();

	float radian = getRadian(position.x, position.y, targetArr[targetIndex].x, targetArr[targetIndex].y);

	SetMoveX(cosf(radian) * speed);
	SetMoveY(sinf(radian) * speed);

	Update();

	//speed active
	if (speed > BOSS_SPEED_MIN) {
		speed -= 0.2f;
	}
	else {
		speed = BOSS_SPEED_MIN;
	}

	//state mode check
	if ((targetArr[targetIndex].x - position.x)*(targetArr[targetIndex].x - position.x) + (targetArr[targetIndex].y - position.y)*(targetArr[targetIndex].y - position.y) <= 10) {
		switch (state) {
		case 0:

			if (activeCount < 1) {
				targetIndex--;
				activeCount++;
			}
			else {
				speed = BOSS_SPEED_MAX;
				targetIndex = 2;
				state = BossState_Move;
			}

			break;
		case 1:
			targetIndex++;
			speed = BOSS_SPEED_MAX;
			if (targetIndex >= 4) {
				targetIndex = 2;
			}

			break;
		case 2:

			break;
		}
	}

	if (state == BossState_Move) {
		Attack();
	}

	

	//collision
	SetCircleCollisionX(position.x + GetWidth() / 2);
	SetCircleCollisionY(position.y + BOSS_Y);
	

	//texture
	aniTime--;
	if (aniTime <= 0) {

		textureX_index++;
		if (textureX_index >= textureX_NUM) {
			textureX_index = 0;
		}

		textureX = GetWidth()*(textureX_index % textureX_NUM);
		aniTime = BOSS_ANIMATION_TIME;

		text_rec.left = textureX;
		text_rec.top = textureY;
		text_rec.right = text_rec.left + GetWidth();
		text_rec.bottom = text_rec.top + GetHeight();
	}

	//demage effect
	if (Effect) {
		SetSpriteColor(D3DCOLOR_ARGB((rand() % 155) + 1, 255, 255, 255));
		Effect_time--;
		if (Effect_time <= 0) {
			Effect = false;
			Effect_time = BOSS_EFFECT_TIME;
			SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

//生命力設定処理
//==================================================
void Boss::SetLife(int Life) {
	life = Life;
	if (life <= 0) {
		life = 0;
	}
}

//スコーア設定処理
//==================================================
void Boss::SetScore(int Score) {
	score = Score;
}

//速度設定処理
//==================================================
void Boss::SetSpeed(float Speed) {
	speed = Speed;
}

//損傷を取る処理
//==================================================
int Boss::GetScore() {
	return score;
}
//損傷を取る処理
//==================================================
int Boss::GetLife() {
	return life;
}
//損傷を取る処理
//==================================================
RECT* Boss::GetRect() {
	return &text_rec;
}

//HPバー初期化処理
//==================================================
void Boss::InitBloodSprite() {
	D3DXCreateSprite(g_d3dDevice, &health_sprite);
	D3DXCreateSprite(g_d3dDevice, &healthUI_sprite);
}

//HPバー解放処理
//==================================================
void Boss::BloodSprite_Uninit() {
	
	health_sprite->Release();
	healthUI_sprite->Release();
}

//HPバーの描画処理
//==================================================
void Boss::DrawBloodSprite(float UIx, float UIy, float BARx, float BARy) {
	//UI BG
	healthUI_Position.x = UIx;
	healthUI_Position.y = UIy;
	healthUI_Position.z = 0;

	healthUI_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	healthUI_sprite->Draw(Texture_GetTexture(BOSS_UI), NULL, NULL, &healthUI_Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	healthUI_sprite->End();

	//BLOOD
	if (life != oldHealth) {
		oldHealth -= (oldHealth - life);
		if (oldHealth <= 0) {
			oldHealth = 0;
		}
		health_percent = oldHealth / BOSS_HEALTHBAR_TOTAL;
	}

	health_Position.x = BARx;
	health_Position.y = BARy;
	health_Position.z = 0;

	health_rec.left = 0;
	health_rec.top = 0;
	health_rec.right = health_rec.left + BOSS_HEALTHBAR_WIDTH * health_percent;
	health_rec.bottom = health_rec.top + BOSS_HEALTHBAR_HEIGHT;

	health_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	health_sprite->Draw(Texture_GetTexture(BOSS_HPBAR), &health_rec, NULL, &health_Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	health_sprite->End();
}

//行動フラグ設定
//==================================================
void Boss::SetActiveflag(bool flag) {
	bossActiv = flag;
}

//行動フラグ取る
//==================================================
bool Boss::GetActiveflag() {
	return bossActiv;
}

//当てられたら傷害の効果を表示する時間設定
//==================================================
void Boss::SetDamageEffect(bool sw) {
	Effect = sw;
	Effect_time = BOSS_EFFECT_TIME;
}

//体の傷害値を取る
//==================================================
int Boss::GetEnemyBodyDamage() {
	return bodydamage;
}

//ラジアン計算処理
//==================================================
float Boss::getRadian(float X1, float Y1, float X2, float Y2) {
	float w = X2 - X1;
	float h = Y2 - Y1;

	return atan2f(h, w);
}

//目標の座標を設定する
//==================================================
void Boss::SetTargetArr(Vector2D MtargetArr) {
	targetArr[targetIndex].x = MtargetArr.x;
	targetArr[targetIndex].y = MtargetArr.y;
	targetIndex++;
}

//目標の座標配列を消す
//==================================================
void Boss::DeletTargetArr() {
	for (int i = 0;i < BOSS_TARGET;i++) {
		targetArr[i] = { 0 };
	}
}

//目標のインデックスを設定する
//==================================================
void Boss::SetTargetIndex(int index) {
	targetIndex = index;
}

//攻撃処理
//==================================================
void Boss::Attack() {
	attackTime--;
	if (attackTime <= 0) {
		BulletManager::BossBullet_Create(GetCircleCollision()->cx, GetCircleCollision()->cy);
		attackTime = BOSS_ATTACK_TIME;
	}

	//big bullet
	BigattackTime--;
	if (BigattackTime <= 0) {
		BulletManager::BossBigBullet_Create(GetCircleCollision()->cx, GetCircleCollision()->cy);

		if (life > 10) {
			BigattackTime = BOSS_BIGATTACK_TIME_MAX;
		}
		else {
			BigattackTime = BOSS_BIGATTACK_TIME_MIN;
		}
		
	}
}