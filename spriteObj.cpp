#include "texture.h"
#include "SpriteObj.h"
#include "direct3d_setup.h"

SpriteObj::SpriteObj()
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

void SpriteObj::InitSprite() {
	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	D3DXCreateSprite(g_pD3DDevice, &sprite);
}

void SpriteObj::Update()
{
	position.x += move.x;
	position.y += move.y;
}

void SpriteObj::Draw()
{
	//Sprite_Draw(TextureIndex, position.x, position.y);
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), NULL, NULL, &Position, color);

	sprite->End();
}

void SpriteObj::DrawCut() {
	Sprite_Draw(TextureIndex, position.x, position.y, 64, 0, 64, 64);
}

void SpriteObj::SetObjectData(Vector2D pos, float wid, float hei)
{
	position = pos;
	width = wid;
	height = hei;
	isLive = true;
}

void SpriteObj::SetPosition(Vector2D pos)
{
	position = pos;
}

void SpriteObj::SetMoveX(float x)
{
	move.x = x;
}


void SpriteObj::SetMoveY(float y)
{
	move.y = y;
}

void SpriteObj::SetWidth(float wid)
{
	width = wid;
}

void SpriteObj::SetHeight(float hei)
{
	height = hei;
}

void SpriteObj::SetLiveFlag(bool flag)
{
	isLive = flag;
}

void SpriteObj::SetTextureIndex(int index) {
	TextureIndex = index;
}

void SpriteObj::SetPositionX(float x) {
	position.x = x;
}

void SpriteObj::SetPositionY(float y) {
	position.y = y;
}

void SpriteObj::SetCircleCollision(Circle objCollision) {
	g_CircleCollision = objCollision;
}

void SpriteObj::SetCircleCollisionX(float x) {
	g_CircleCollision.cx = x;
}

void SpriteObj::SetCircleCollisionY(float y) {
	g_CircleCollision.cy = y;
}

Vector2D SpriteObj::GetPosition() {
	return position;
}

float SpriteObj::GetWidth() {
	return width;
}

float SpriteObj::GetHeight() {
	return height;
}

bool SpriteObj::GetLiveFlag() {
	return isLive;
}

int SpriteObj::GetTextureIndex() {
	return TextureIndex;
}

Circle* SpriteObj::GetCircleCollision() {
	return &g_CircleCollision;
}

SpriteObj::~SpriteObj()
{

}