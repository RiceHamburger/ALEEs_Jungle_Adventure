//==================================================
//  �v���[���[�N���X [player.cpp]        Autor:��
//==================================================
#include "D3DInput.h"
#include "player.h"
#include "bulletManager.h"
#include "background.h"
#include "Judgment.h"
#include "sound.h"
#include "D3Dsetup.h"

//�v���[���[�̈ړ����x
#define PLAYER_MOVE_SPEED (0.1f)
//�e�̑��x
#define BULLET_SPEED (1.0f)

//�C���X�^���X
//==================================================
Player::Player()
{
	score = 0;
	isMove = false;
	WalkRank = NULL;
}

//�f�X�g���N�^
//==================================================
Player::~Player()
{
	
}

//�v���[���[�R���g���[��
//==================================================
void Player::PlayerControl()
{
	D3DXVECTOR2 vecDir(0.0f, 0.0f);

	//��Ɉړ�����
	if (gDInput->keyDown(DIK_W)) {

		if (RangCheck(GetPosition().x, GetPosition().y - 1)) {
			vecDir.y += -1.0f;
			isMove = true;

			textureY_index = PlayerState_Front;
			state = PlayerState_Front;
		}

	}else if(gDInput->keyDown(DIK_S)) {//���Ɉړ�����

		if (RangCheck(GetPosition().x, GetPosition().y + 64 + 1)) {
			vecDir.y += 1.0f;
			isMove = true;

			textureY_index = PlayerState_Back;
			state = PlayerState_Back;
		}

	}

	//���Ɉړ�����
	if (gDInput->keyDown(DIK_A)) {

		if (RangCheck(GetPosition().x - 1, GetPosition().y)) {
			vecDir.x += -1.0f;
			isMove = true;

			textureY_index = PlayerState_Left;
			state = PlayerState_Left;
		}

	}else if (gDInput->keyDown(DIK_D)) {//�E�Ɉړ�����

		if (RangCheck(GetPosition().x + 64 + 1, GetPosition().y)) {
			vecDir.x += 1.0f;
			isMove = true;

			textureY_index = PlayerState_Right;
			state = PlayerState_Right;
		}
	}
	

	//�m�[�}���C�Y
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

	//�v���C���[�̍��W���m��
	if (gDInput->keyIsTrigger(DIK_SPACE)) {

		if (ShootedNum >= 3 && !canHighShoot)return;
		//player shoot
		PlaySound(SOUND_LABEL_SE_SHOT);

		//�A��Shoot��INIT
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

	//���G
	if (invincible) {
		SetSpriteColor(D3DCOLOR_ARGB((rand() % 155) + 1, 255, 255, 255));
		invincible_time--;
		if (invincible_time <= 0) {
			invincible = false;
			invincible_time = PLAYER_INVINCIBLE_TIME;
			SetSpriteColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	//Item���g��
	if (gDInput->keyDown(DIK_Z)) {
		if (haveItem) {
			SetHighShoot(true);
			haveItem = false;
		}
	}

	//�A��Shoot�o����
	checkContinuous();
	//�A��SHOOT����
	checkHightShoot();
}

//�v���[���[�A�j���[�V����
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

// ����������
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

	//���G
	invincible = false;
	invincible_time = PLAYER_INVINCIBLE_TIME;

	//�A��Shoot
	renzokuShoot = false;

	//can't high shoot
	canHighShoot = false;

	//�e�̐��ʏ�����
	ShootedNum = 0;

	//have Item
	haveItem = false;
}

// �����͐ݒ菈��
//==================================================
void Player::SetLife(int Life) {
	life = Life;
}

// �X�R�[�A�ݒ菈��
//==================================================
void Player::SetScore(int Score) {
	score = Score;
}

// ��Ԑݒ菈��
//==================================================
void Player::SetState(PlayerState State) {
	state = State;
}

// �X�R�[�A�����
//==================================================
int Player::GetScore() {
	return score;
}

// �����͂����
//==================================================
int Player::GetLife() {
	return life;
}

// �X�R�[�A�𑝂₷
//==================================================
void Player::AddScore(int addscore) {
	score += addscore;
}

// �͈͂����
//==================================================
RECT* Player::GetRect() {
	return &text_rec;
}

// ���G��Ԃ̃t���O��ݒ�
//==================================================
void Player::SetInvincible(bool sw) {
	invincible = sw;
}

// ���G��Ԃ̃t���O�����
//==================================================
bool Player::GetInvincible() {
	return invincible;
}

// ������͈͂̐�����ݒ�
//==================================================
void Player::SetWalkRang(int* rang) {
	WalkRank = rang;
}

// ������͈͌v�Z����
//==================================================
bool Player::RangCheck(float x, float y) {
	int gx = x / 32;
	int gy = y / 32;
	return *(WalkRank + gy*MAP_NUM_X + gx) == 0;
}

// �V���[�e�B���O�Ԋu����
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

// �n�C�V���[�e�B���OMODE�ݒ�
//==================================================
void Player::SetHighShoot(bool sw) {
	canHighShoot = sw;
	if (canHighShoot) {
		HighShootTime = HIGHT_SHOOTE_TIME;
	}
}

// �n�C�V���[�e�B���O�Ԋu����
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

// �A�C�e�����������Ԃ��`�F�b�N����
//==================================================
bool Player::GetItemCheck(void) {
	return haveItem;
}

// �A�C�e�����������Ԃ�ݒ肷��
//==================================================
void Player::SetItemCheck(bool sw) {
	haveItem = sw;
}