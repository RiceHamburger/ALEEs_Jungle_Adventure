#include "enemy_red.h"
#include "D3Dsetup.h"
#include "bulletManager.h"

//�R���X�g���N�^
//==================================================
EnemyRed::EnemyRed() {

}

//�f�X�g���N�^
//==================================================
EnemyRed::~EnemyRed() {

}

// ����������
//==================================================
void EnemyRed::InitEnemy(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(ENEMY_WIDTH);
	SetHeight(ENEMY_HEIGHT);
	//����̉~��ݒ肷��
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

	//�ڂ͈̔�
	objCollision.cx = pos.x + GetHeight() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetHeight()*10.0f;
	g_CircleSeeCollision = objCollision;
	thisAngle = 90;
}

//�ڕW�̃C���f�b�N�X��ݒ肷��
//==================================================
void EnemyRed::SetTargetIndex(int index) {
	targetIndex = index;
}

//�X�V����
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

//�G�l�~�[���폜����
//==================================================
void EnemyRed::EnemyDestroy() {
	SetLiveFlag(false);
}

//HP�ݒ�
//==================================================
void EnemyRed::SetLife(int Life) {
	life = Life;
	if (life <= 0) {
		life = 0;
	}
}

//�X�R�[�A�ݒ�
//==================================================
void EnemyRed::SetScore(int Score) {
	score = Score;
}

//�X�s�[�h�ݒ�
//==================================================
void EnemyRed::SetSpeed(float Speed) {
	speed = Speed;
}

//�X�s�[�h�����
//==================================================
float EnemyRed::GetSpeed() {
	return speed;
}

//�X�R�[�A�����
//==================================================
int EnemyRed::GetScore() {
	return score;
}

//�G�l�~�[�͈͂����
//==================================================
RECT* EnemyRed::GetRect() {
	return &text_rec;
}

//HP�����
//==================================================
int EnemyRed::GetLife() {
	return life;
}

//���W�A���v�Z����
//==================================================
float EnemyRed::getRadian(float X1, float Y1, float X2, float Y2) {
	float w = X2 - X1; // cos��
	float h = Y2 - Y1; // sin��

	// atan2f�ĂԂ����ł����܂�
	return atan2f(h, w);
}

//�G�l�~�[�̑̂̏����l�����
//==================================================
int EnemyRed::GetEnemyBodyDamage() {
	return bodydamage;
}

//HP�o�[����������
//==================================================
void EnemyRed::InitBloodSprite() {
	D3DXCreateSprite(g_d3dDevice, &health_sprite);
}

//HP�o�[�p������
//==================================================
void EnemyRed::BloodSprite_Uninit() {
	health_sprite->Release();
}

//HP�o�[�̕`�揈��
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

//�G�l�~�[�U������
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

//���Ă�ꂽ�珝�Q�̌��ʂ�\�����鎞�Ԑݒ�
//==================================================
void EnemyRed::SetDamageEffect(bool sw) {
	Effect = sw;
	Effect_time = ENEMY_EFFECT_TIME;
}


//�U���J�n�͈͂����
//==================================================
Circle* EnemyRed::GetSeeCircleCollision() {
	return &g_CircleSeeCollision;
}

//�p�x���Z�b�g����
//==================================================
void EnemyRed::AngleReset(void) {
	thisAngle = 90;
}