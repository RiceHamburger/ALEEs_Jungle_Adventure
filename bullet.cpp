#include "bullet.h"
#define MAP_NUM_X (84)

Bullet::Bullet() {

}
Bullet::~Bullet() {

}

void Bullet::InitBullet(Vector2D pos, TEXTURE_NAME tex_name) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	//SetWidth(BULLET_WIDTH);
	SetWidth(Texture_GetWidth(tex_name));
	SetHeight(Texture_GetHeight(tex_name));

	//判定の円を設定する
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetWidth()*0.5f;
	SetCircleCollision(objCollision);
}

void Bullet::BulletActive() {
	Vector2D position = GetPosition();

	SetMoveX(speedX);
	SetMoveY(speedY);

	SetCircleCollisionX(position.x + GetWidth() / 2);
	SetCircleCollisionY(position.y + GetWidth() / 2);

	//Tree当たり判定
	if (!RangCheck(position.x + 1, position.y + 1)) {
		SetLiveFlag(false);
	}


	if (position.x > SCREEN_WIDTH*2.55 || position.x < -64 || position.y < 0 || position.y > SCREEN_HEIGHT + 230) {
		SetLiveFlag(false);
	}

	Update();
}

void Bullet::BulletDestroy() {
	SetLiveFlag(false);
}

void Bullet::SetSpeed(float Speedx, float Speedy) {
	speedX = Speedx;
	speedY = Speedy;
}

/*float Bullet::GetSpeed() {
	return speed;
}*/

void Bullet::SetDamage(int hit) {
	bulletDamage = hit;
}

int Bullet::GetDamage() {
	return bulletDamage;
}

//範囲セット
void Bullet::SetWalkRang(int* rang) {
	MoveRank = rang;
}

//範囲チェック
bool Bullet::RangCheck(float x, float y) {
	int gx = x / 32;
	int gy = y / 32;
	return *(MoveRank + gy*MAP_NUM_X + gx) == 0;
}