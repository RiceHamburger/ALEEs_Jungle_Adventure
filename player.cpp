//==================================================
//  プレーヤークラス [player.cpp]        Autor:ロ
//==================================================
#include "D3DInput.h"
#include "player.h"
#include "bulletManager.h"
#include "background.h"
#include "Judgment.h"
#include "sound.h"
#include "D3Dsetup.h"

//プレーヤーの移動速度
#define PLAYER_MOVE_SPEED (0.1f)
//弾の速度
#define BULLET_SPEED (1.0f)

//インスタンス
//==================================================
Player::Player()
{
	score = 0;
	isMove = false;
	WalkRank = NULL;
}

//デストラクタ
//==================================================
Player::~Player()
{
	
}

//プレーヤーコントロール
//==================================================
void Player::PlayerControl()
{
	D3DXVECTOR2 vecDir(0.0f, 0.0f);

	//上に移動する
	if (gDInput->keyDown(DIK_W)) {

		if (RangCheck(GetPosition().x, GetPosition().y - 1)) {
			vecDir.y += -1.0f;
			isMove = true;

			textureY_index = PlayerState_Front;
			state = PlayerState_Front;
		}

	}else if(gDInput->keyDown(DIK_S)) {//下に移動する

		if (RangCheck(GetPosition().x, GetPosition().y + 64 + 1)) {
			vecDir.y += 1.0f;
			isMove = true;

			textureY_index = PlayerState_Back;
			state = PlayerState_Back;
		}

	}

	//左に移動する
	if (gDInput->keyDown(DIK_A)) {

		if (RangCheck(GetPosition().x - 1, GetPosition().y)) {
			vecDir.x += -1.0f;
			isMove = true;

			textureY_index = PlayerState_Left;
			state = PlayerState_Left;
		}

	}else if (gDInput->keyDown(DIK_D)) {//右に移動する

		if (RangCheck(GetPosition().x + 64 + 1, GetPosition().y)) {
			vecDir.x += 1.0f;
			isMove = true;

			textureY_index = PlayerState_Right;
			state = PlayerState_Right;
		}
	}
	

	//ノーマライズ
	D3DXVec2Normalize(&vecDir, &vecDir);
	g_PlayerSpeed += vecDir * PLAYER_MOVE_SPEED;

	
	SetMoveX(g_PlayerSpeed.x);
	SetMoveY(g_PlayerSpeed.y);
	g_PlayerSpeed *= 0.8f;
	

	SetPositionX(max(GetPosition().x, -GetWidth() * 0.5));
	SetPositionX(min(GetPosition().x, SCREEN_WIDTH * 2.5 + 94));
	SetPositionY(max(GetPosition().y, -GetHeight() * 0.5));
	SetPositionY(min(GetPosition().y, SCREEN_HEIGHT + GetHeight()*3));

	SetCircleCollisionX(GetPosition().x + GetWidth() / 2);
	SetCircleCollisionY(GetPosition().y + GetWidth() / 2);

	//プレイヤーの座標が確定
	if (gDInput->keyIsTrigger(DIK_SPACE)) {

		if (ShootedNum >= 3 && !canHighShoot)return;
		//player shoot
		PlaySound(SOUND_LABEL_SE_SHOT);

		//連続ShootのINIT
		renzokuShoot = true;
		canShootTime = SHOOTE_TIME;

		switch (state)
		{
		case PlayerState_Front:
			BulletManager::Bullet_Create(GetPosition().x + GetWidth() / 2, GetPosition().y,0, -BULLET_SPEED);
			break;
		case PlayerState_Left:
			BulletManager::Bullet_Create(GetPosition().x, GetPosition().y + GetHeight() / 2, -BULLET_SPEED, 0);
			break;
		case PlayerState_Back:
			BulletManager::Bullet_Create(GetPosition().x + GetWidth() / 2, GetPosition().y + GetHeight(), 0, BULLET_SPEED);
			break;
		case PlayerState_Right:
			BulletManager::Bullet_Create(GetPosition().x + GetWidth(), GetPosition().y + GetHeight() / 2, BULLET_SPEED, 0);
			break;
		default:
			break;
		}

		//shootedNum add
		ShootedNum++;
	}

	if (isMove && vecDir.x == 0 && vecDir.y == 0) {
		isMove = false;
		aniTime = PLAYER_ANIMATION_TIME;

		textureX_index = 0;
		textureX = GetWidth()*(textureX_index % textureX_NUM);
		text_rec.left = textureX;
		text_rec.top = textureY;
		text_rec.right = text_rec.left + GetWidth();
		text_rec.bottom = text_rec.top + GetHeight();
	}

	//player animation
	PlayerAni();

	//無敵
	if (invincible) {
		SetSpriteColor(D3DCOLOR_ARGB((rand() % 155) + 1, 255, 255, 255));
		invincible_time--;
		if (invincible_time <= 0) {
			invincible = false;
			invincible_time = PLAYER_INVINCIBLE_TIME;
			SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	//Itemを使う
	if (gDInput->keyDown(DIK_Z)) {
		if (haveItem) {
			SetHighShoot(true);
			haveItem = false;
		}
	}

	//連続Shoot出来る
	checkContinuous();
	//連続SHOOT時間
	checkHightShoot();
}

//プレーヤーアニメーション
//==================================================
void Player::PlayerAni() {

	if (!isMove)return;

	aniTime--;
	if (aniTime <= 0) {

		textureX_index++;
		if (textureX_index >= textureX_NUM) {
			textureX_index = 0;
		}

		textureX = GetWidth()*(textureX_index % textureX_NUM);
		textureY = GetHeight()*(textureY_index % textureY_NUM);
		aniTime = PLAYER_ANIMATION_TIME;

		text_rec.left = textureX;
		text_rec.top = textureY;
		text_rec.right = text_rec.left + GetWidth();
		text_rec.bottom = text_rec.top + GetHeight();
	}
}

// 初期化処理
//==================================================
void Player::InitPlayer(Vector2D pos,PlayerState State, D3DXVECTOR2 PlayerSpeed, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY) {
	//animation
	textureX = 0;
	textureY = 0;
	textureX_index = 0;
	textureY_index = 0;
	textureX_NUM = tex_pic_numX;
	textureY_NUM = tex_pic_numY;
	aniTime = PLAYER_ANIMATION_TIME;

	//state
	state = State;

	g_PlayerSpeed = PlayerSpeed;
	SetTextureIndex(tex_name);
	SetObjectData(pos, Texture_GetWidth(tex_name)/ textureX_NUM, Texture_GetHeight(tex_name)/ textureY_NUM);

	isMove = false;
	text_rec.left = textureX;
	text_rec.top = textureY;
	text_rec.right = text_rec.left + GetWidth();
	text_rec.bottom = text_rec.top + GetHeight();

	//collision
	Circle objCollision;
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetWidth()*0.2f;
	SetCircleCollision(objCollision);

	//無敵
	invincible = false;
	invincible_time = PLAYER_INVINCIBLE_TIME;

	//連続Shoot
	renzokuShoot = false;

	//can't high shoot
	canHighShoot = false;

	//弾の数量初期化
	ShootedNum = 0;

	//have Item
	haveItem = false;
}

// 生命力設定処理
//==================================================
void Player::SetLife(int Life) {
	life = Life;
}

// スコーア設定処理
//==================================================
void Player::SetScore(int Score) {
	score = Score;
}

// 状態設定処理
//==================================================
void Player::SetState(PlayerState State) {
	state = State;
}

// スコーアを取る
//==================================================
int Player::GetScore() {
	return score;
}

// 生命力を取る
//==================================================
int Player::GetLife() {
	return life;
}

// スコーアを増やす
//==================================================
void Player::AddScore(int addscore) {
	score += addscore;
}

// 範囲を取る
//==================================================
RECT* Player::GetRect() {
	return &text_rec;
}

// 無敵状態のフラグを設定
//==================================================
void Player::SetInvincible(bool sw) {
	invincible = sw;
}

// 無敵状態のフラグを取る
//==================================================
bool Player::GetInvincible() {
	return invincible;
}

// 動ける範囲の数字を設定
//==================================================
void Player::SetWalkRang(int* rang) {
	WalkRank = rang;
}

// 動ける範囲計算処理
//==================================================
bool Player::RangCheck(float x, float y) {
	int gx = x / 32;
	int gy = y / 32;
	return *(WalkRank + gy*MAP_NUM_X + gx) == 0;
}

// シューティング間隔処理
//==================================================
void Player::checkContinuous(void) {
	if (renzokuShoot) {
		canShootTime--;
		if (canShootTime <= 0) {
			renzokuShoot = false;
			canShootTime = SHOOTE_TIME;
			ShootedNum = 0;
		}
	}
}

// ハイシューティングMODE設定
//==================================================
void Player::SetHighShoot(bool sw) {
	canHighShoot = sw;
	if (canHighShoot) {
		HighShootTime = HIGHT_SHOOTE_TIME;
	}
}

// ハイシューティング間隔処理
//==================================================
void Player::checkHightShoot(void) {
	if (canHighShoot) {
		HighShootTime--;
		if (HighShootTime <= 0) {
			canHighShoot = false;
			ShootedNum = 0;
		}
	}
}

// アイテムを取った状態をチェックする
//==================================================
bool Player::GetItemCheck(void) {
	return haveItem;
}

// アイテムを取った状態を設定する
//==================================================
void Player::SetItemCheck(bool sw) {
	haveItem = sw;
}