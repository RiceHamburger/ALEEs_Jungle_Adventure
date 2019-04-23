//==================================================
// アイテムクラス [tonic.cpp]        Autor:ロ
//==================================================
#include "tonic.h"

//インスタンス
//==================================================
Tonic::Tonic() {

}
//デストラクタ
//==================================================
Tonic::~Tonic() {

}

// 初期化処理
//==================================================
void Tonic::InitTonic(Vector2D pos, TEXTURE_NAME tex_name,TonicState state) {
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

	addHealth = TONIC_ADD_HEALTH;
	this_TonicState = state;
}

//更新処理
//==================================================
void Tonic::TonicActive() {

}

//廃棄処理
//==================================================
void Tonic::TonicDestroy() {
	SetLiveFlag(false);
}

//生命力を取る
//==================================================
int Tonic::GetAddHealth() {
	return addHealth;
}

//コリジョンを取る
//==================================================
void Tonic::resetCollision() {
	Vector2D position = GetPosition();
	SetCircleCollisionX(position.x + GetWidth() / 2);
	SetCircleCollisionY(position.y + GetWidth() / 2);
}

//アイテムのタイプを取る
//==================================================
int Tonic::GetState() {
	return this_TonicState;
}