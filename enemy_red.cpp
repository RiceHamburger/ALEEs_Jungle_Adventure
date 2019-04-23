#include "enemy_red.h"
#include "D3Dsetup.h"
#include "bulletManager.h"

//コンストラクタ
//==================================================
EnemyRed::EnemyRed() {

}

//デストラクタ
//==================================================
EnemyRed::~EnemyRed() {

}

// 初期化処理
//==================================================
void EnemyRed::InitEnemy(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(ENEMY_WIDTH);
	SetHeight(ENEMY_HEIGHT);
	//判定の円を設定する
	objCollision.cx = pos.x + GetHeight() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetHeight()*0.5f;
	SetCircleCollision(objCollision);
	this->SetLiveFlag(true);

	targetIndex = 0;
	bodydamage = ENEMY_BODYDAMAGE;
	SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));

	//sprite rect
	textureX = 0;
	textureY = 0;
	textureX_index = 0;
	textureY_index = 0;
	textureX_NUM = tex_pic_numX;
	textureY_NUM = tex_pic_numY;
	aniTime = ENEMY_ANIMATION_TIME;
	text_rec.left = textureX;
	text_rec.top = textureY;
	text_rec.right = text_rec.left + GetHeight();
	text_rec.bottom = text_rec.top + GetHeight();

	health_percent = 1.0f;

	//attack time
	attackTime = ENEMY_ATTACK_TIME;
	Effect = false;
	Effect_time = ENEMY_EFFECT_TIME;

	//目の範囲
	objCollision.cx = pos.x + GetHeight() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetHeight()*10.0f;
	g_CircleSeeCollision = objCollision;
	thisAngle = 90;
}

//目標のインデックスを設定する
//==================================================
void EnemyRed::SetTargetIndex(int index) {
	targetIndex = index;
}

//更新処理
//==================================================
void EnemyRed::EnemyActive() {
	Vector2D position = GetPosition();

	SetCircleCollisionX(position.x + GetHeight() / 2);
	SetCircleCollisionY(position.y + GetHeight() / 2);

	//texture
	aniTime--;
	if (aniTime <= 0) {

		textureX_index++;
		if (textureX_index >= textureX_NUM) {
			textureX_index = 0;

			textureY_index++;
			if (textureY_index >= textureY_NUM) {
				textureY_index = 0;
			}
		}

		textureX = GetWidth()*(textureX_index % textureX_NUM);
		textureY = GetHeight()*(textureY_index % textureY_NUM);
		aniTime = ENEMY_ANIMATION_TIME;

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
			Effect_time = ENEMY_EFFECT_TIME;
			SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

//エネミーを削除処理
//==================================================
void EnemyRed::EnemyDestroy() {
	SetLiveFlag(false);
}

//HP設定
//==================================================
void EnemyRed::SetLife(int Life) {
	life = Life;
	if (life <= 0) {
		life = 0;
	}
}

//スコーア設定
//==================================================
void EnemyRed::SetScore(int Score) {
	score = Score;
}

//スピード設定
//==================================================
void EnemyRed::SetSpeed(float Speed) {
	speed = Speed;
}

//スピードを取る
//==================================================
float EnemyRed::GetSpeed() {
	return speed;
}

//スコーアを取る
//==================================================
int EnemyRed::GetScore() {
	return score;
}

//エネミー範囲を取る
//==================================================
RECT* EnemyRed::GetRect() {
	return &text_rec;
}

//HPを取る
//==================================================
int EnemyRed::GetLife() {
	return life;
}

//ラジアン計算処理
//==================================================
float EnemyRed::getRadian(float X1, float Y1, float X2, float Y2) {
	float w = X2 - X1; // cosθ
	float h = Y2 - Y1; // sinθ

	// atan2f呼ぶだけでおしまい
	return atan2f(h, w);
}

//エネミーの体の処理値を取る
//==================================================
int EnemyRed::GetEnemyBodyDamage() {
	return bodydamage;
}

//HPバー初期化処理
//==================================================
void EnemyRed::InitBloodSprite() {
	D3DXCreateSprite(g_d3dDevice, &health_sprite);
}

//HPバー廃棄処理
//==================================================
void EnemyRed::BloodSprite_Uninit() {
	health_sprite->Release();
}

//HPバーの描画処理
//==================================================
void EnemyRed::DrawBloodSprite() {
	Vector2D Myposition = GetPosition();

	D3DXVECTOR3 Position;
	Position.x = Myposition.x + 5;
	Position.y = Myposition.y - ENEMY_HEALTHBAR_HEIGHT;
	Position.z = 0;

	health_percent = (float)life / ENEMY_HEALTHBAR_TOTAL;

	health_rec.left = 0;
	health_rec.top = 0;
	health_rec.right = health_rec.left + ENEMY_HEALTHBAR_WIDTH * health_percent;
	health_rec.bottom = health_rec.top + ENEMY_HEALTHBAR_HEIGHT;

	health_sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	health_sprite->Draw(Texture_GetTexture(ENEMYBAR), &health_rec, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	health_sprite->End();
}

//エネミー攻撃処理
//==================================================
void EnemyRed::EnemyAttack() {
	attackTime--;
	if (attackTime <= 0) {
		BulletManager::EnemyRedBullet_Create(GetPosition().x + GetWidth() / 2 - BULLET_WIDTH/2, GetPosition().y + GetHeight() / 2, thisAngle);
		attackTime = ENEMY_ATTACK_TIME;


		thisAngle+=25;
		if (thisAngle >= 360) {
			thisAngle = 90;
		}
	}
	
}

//当てられたら傷害の効果を表示する時間設定
//==================================================
void EnemyRed::SetDamageEffect(bool sw) {
	Effect = sw;
	Effect_time = ENEMY_EFFECT_TIME;
}


//攻撃開始範囲を取る
//==================================================
Circle* EnemyRed::GetSeeCircleCollision() {
	return &g_CircleSeeCollision;
}

//角度リセット処理
//==================================================
void EnemyRed::AngleReset(void) {
	thisAngle = 90;
}