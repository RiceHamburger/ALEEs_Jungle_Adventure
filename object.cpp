#include "texture.h"
#include "object.h"

//コンストラクタ
//==================================================
Object::Object()
{
	position = { 0.0f };
	move = { 0.0f };
	width = 0.0f;
	height = 0.0f;
	isLive = false;
	TextureIndex = 0;
	g_CircleCollision = { 0 };
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

// 初期化処理
//==================================================
void Object::InitSprite() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

//更新処理
//==================================================
void Object::Update()
{
	//移動量を加算
	position.x += move.x;
	position.y += move.y;
}

// 描画処理
//==================================================
void Object::DrawSprite() {
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), NULL, NULL, &Position, color);

	sprite->End();
}

// 描画処理（表示範囲）
//==================================================
void Object::DrawSprite(RECT* text_rec) {
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), text_rec, NULL, &Position, color);

	sprite->End();
}

// オブジェクト設定処理
//==================================================
void Object::SetObjectData(Vector2D pos, float wid, float hei)
{
	position = pos;
	width = wid;
	height = hei;
	isLive = true;
}

// 座標設定
//==================================================
void Object::SetPosition(Vector2D pos)
{
	position = pos;
}

// X軸移動ベクトル更新
//==================================================
void Object::SetMoveX(float x)
{
	move.x = x;
}

// Y軸移動ベクトル更新
//==================================================
void Object::SetMoveY(float y)
{
	move.y = y;
}

// 広さ設定
//==================================================
void Object::SetWidth(float wid)
{
	width = wid;
}

// 高さ設定
//==================================================
void Object::SetHeight(float hei)
{
	height = hei;
}

// 実行チェック用フラグ設定
//==================================================
void Object::SetLiveFlag(bool flag)
{
	isLive = flag;
}

// テクスチャインデックス設定
//==================================================
void Object::SetTextureIndex(int index) {
	TextureIndex = index;
}

// X座標設定
//==================================================
void Object::SetPositionX(float x) {
	position.x = x;
}

// Y座標設定
//==================================================
void Object::SetPositionY(float y) {
	position.y = y;
}

// 円コリジョン設定
//==================================================
void Object::SetCircleCollision(Circle objCollision) {
	g_CircleCollision = objCollision;
}

// 円コリジョンのX座標設定
//==================================================
void Object::SetCircleCollisionX(float x) {
	g_CircleCollision.cx = x;
}

// 円コリジョンのY座標設定
//==================================================
void Object::SetCircleCollisionY(float y) {
	g_CircleCollision.cy = y;
}

// 座標を取る
//==================================================
Vector2D Object::GetPosition() {
	return position;
}

// 広さを取る
//==================================================
float Object::GetWidth() {
	return width;
}

// 高さを取る
//==================================================
float Object::GetHeight() {
	return height;
}

// 座標を取る
//==================================================
bool Object::GetLiveFlag() {
	return isLive;
}

// テクスチャインデックスを取る
//==================================================
int Object::GetTextureIndex() {
	return TextureIndex;
}

// コリジョンを取る
//==================================================
Circle* Object::GetCircleCollision() {
	return &g_CircleCollision;
}

//デストラクタ
//==================================================
Object::~Object()
{

}

//終了処理
//==================================================
void Object::Sprite_Uninit() {
	sprite->Release();
}

// スプライト色を取る
//==================================================
void Object::SetSpriteColor(D3DCOLOR Rgba) {
	color = Rgba;
}