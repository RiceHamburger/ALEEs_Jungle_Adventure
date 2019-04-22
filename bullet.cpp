#include "bullet.h"
#define MAP_NUM_X (84)

//�R���X�g���N�^
//==================================================
Bullet::Bullet() {

}
//�f�X�g���N�^
//==================================================
Bullet::~Bullet() {

}
//����������
//==================================================
void Bullet::InitBullet(Vector2D pos, TEXTURE_NAME tex_name) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(Texture_GetWidth(tex_name));
	SetHeight(Texture_GetHeight(tex_name));

	//����̉~��ݒ肷��
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetWidth()*0.5f;
	SetCircleCollision(objCollision);
}

//�X�V����
//==================================================
void Bullet::BulletActive() {
	Vector2D position = GetPosition();

	SetMoveX(speedX);
	SetMoveY(speedY);

	SetCircleCollisionX(position.x + GetWidth() / 2);
	SetCircleCollisionY(position.y + GetWidth() / 2);

	//Tree�����蔻��
	if (!RangCheck(position.x + 1, position.y + 1)) {
		SetLiveFlag(false);
	}


	if (position.x > SCREEN_WIDTH*2.55 || position.x < -64 || position.y < 0 || position.y > SCREEN_HEIGHT + 230) {
		SetLiveFlag(false);
	}

	Update();
}

//��������
//==================================================
void Bullet::BulletDestroy() {
	SetLiveFlag(false);
}

//���x�ݒ菈��
//==================================================
void Bullet::SetSpeed(float Speedx, float Speedy) {
	speedX = Speedx;
	speedY = Speedy;
}

//�����ݒ菈��
//==================================================
void Bullet::SetDamage(int hit) {
	bulletDamage = hit;
}

//��������鏈��
//==================================================
int Bullet::GetDamage() {
	return bulletDamage;
}

//�͈̓Z�b�g
//==================================================
void Bullet::SetWalkRang(int* rang) {
	MoveRank = rang;
}

//�͈̓`�F�b�N
//==================================================
bool Bullet::RangCheck(float x, float y) {
	int gx = x / 32;
	int gy = y / 32;
	return *(MoveRank + gy*MAP_NUM_X + gx) == 0;
}