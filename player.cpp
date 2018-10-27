#include "input.h"
#include "player.h"
#include "bullet_Manager.h"
#include "background.h"
#include "Effect.h"
#include "judgment.h"
#include "sound.h"

#define PLAYER_MOVE_SPEED (0.8f)
#define BULLET_SPEED (10.0f)

Player::Player()
{
	score = 0;
	isMove = false;
	WalkRank = NULL;
}

Player::~Player()
{
	
}

void Player::PlayerControl()
{
	D3DXVECTOR2 vecDir(0.0f, 0.0f);

	//上に移動する
	if (Keyboard_IsPress(DIK_W) || Keyboard_IsPress(DIK_UP) || Xinput_IsTrigger(XINPUT_GAMEPAD_DPAD_UP)) {

		if (RangCheck(GetPosition().x, GetPosition().y - 1)) {
			vecDir.y += -1.0f;
			isMove = true;

			textureY_index = PlayerState_Front;
			state = PlayerState_Front;
		}

	}else if(Keyboard_IsPress(DIK_S) || Keyboard_IsPress(DIK_DOWN) || Xinput_IsTrigger(XINPUT_GAMEPAD_DPAD_DOWN)) {//下に移動する

		if (RangCheck(GetPosition().x, GetPosition().y + 64 + 1)) {
			vecDir.y += 1.0f;
			isMove = true;

			textureY_index = PlayerState_Back;
			state = PlayerState_Back;
		}

	}

	//左に移動する
	if (Keyboard_IsPress(DIK_A) || Keyboard_IsPress(DIK_LEFT) || Xinput_IsTrigger(XINPUT_GAMEPAD_DPAD_LEFT)) {

		if (RangCheck(GetPosition().x - 1, GetPosition().y)) {
			vecDir.x += -1.0f;
			isMove = true;

			textureY_index = PlayerState_Left;
			state = PlayerState_Left;
		}

	}else if (Keyboard_IsPress(DIK_D) || Keyboard_IsPress(DIK_RIGHT) || Xinput_IsTrigger(XINPUT_GAMEPAD_DPAD_RIGHT)) {//右に移動する

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

	//block collision
	//Judgment_Player_vs_Tree(vecDir);

	//プレイヤーの座標が確定
	if (Keyboard_IsTrigger(DIK_SPACE) || Xinput_IsTrigger(XINPUT_GAMEPAD_B)) {
		//player shoot
		PlaySound(SOUND_LABEL_SE_SHOT);

		switch (state)
		{
		case PlayerState_Front:
			Bullet_Create(GetPosition().x + GetWidth() / 2, GetPosition().y,0, -BULLET_SPEED);
			break;
		case PlayerState_Left:
			Bullet_Create(GetPosition().x, GetPosition().y + GetHeight() / 2, -BULLET_SPEED, 0);
			break;
		case PlayerState_Back:
			Bullet_Create(GetPosition().x + GetWidth() / 2, GetPosition().y + GetHeight(), 0, BULLET_SPEED);
			break;
		case PlayerState_Right:
			Bullet_Create(GetPosition().x + GetWidth(), GetPosition().y + GetHeight() / 2, BULLET_SPEED, 0);
			break;
		default:
			break;
		}
	}

	Effect_Creat(GetPosition().x + GetWidth()/2, GetPosition().y + GetHeight() / 2, 32.0f, 60, D3DCOLOR_RGBA(32, 200, 32, 255));

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
}

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
}

void Player::SetLife(int Life) {
	life = Life;
}

void Player::SetScore(int Score) {
	score = Score;
}

void Player::SetState(PlayerState State) {
	state = State;
}

int Player::GetScore() {
	return score;
}

int Player::GetLife() {
	return life;
}

void Player::AddScore(int addscore) {
	score += addscore;
}

RECT* Player::GetRect() {
	return &text_rec;
}

void Player::SetInvincible(bool sw) {
	invincible = sw;
}

bool Player::GetInvincible() {
	return invincible;
}

void Player::SetWalkRang(int* rang) {
	WalkRank = rang;
}

bool Player::RangCheck(float x, float y) {
	int gx = x / 32;
	int gy = y / 32;
	return *(WalkRank + gy*MAP_NUM_X + gx) == 0;
	//return CanWalkRange[gy][gx] == 0;
}