#include "bullet.h"
#define MAP_NUM_X (84)

//コンストラクタ
//==================================================
Bullet::Bullet() {

}
//デストラクタ
//==================================================
Bullet::~Bullet() {

}
//初期化処理
//==================================================
void Bullet::InitBullet(Vector2D pos, TEXTURE_NAME tex_name) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(Texture_GetWidth(tex_name));
	SetHeight(Texture_GetHeight(tex_name));

	//判定の円を設定する
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetWidth()*0.5f;
	SetCircleCollision(objCollision);
}

//更新処理
//==================================================
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

//消す処理
//==================================================
void Bullet::BulletDestroy() {
	SetLiveFlag(false);
}

//速度設定処理
//==================================================
void Bullet::SetSpeed(float Speedx, float Speedy) {
	speedX = Speedx;
	speedY = Speedy;
}

//損傷設定処理
//==================================================
void Bullet::SetDamage(int hit) {
	bulletDamage = hit;
}

//損傷を取る処理
//==================================================
int Bullet::GetDamage() {
	return bulletDamage;
}

//範囲セット
//==================================================
void Bullet::SetWalkRang(int* rang) {
	MoveRank = rang;
}

//範囲チェック
//==================================================
bool Bullet::RangCheck(float x, float y) {
	int gx = x / 32;
	int gy = y / 32;
	return *(MoveRank + gy*MAP_NUM_X + gx) == 0;
}