#include "texture.h"
#include "object.h"

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

void Object::InitSprite() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

void Object::Update()
{
	position.x += move.x;
	position.y += move.y;
}

void Object::DrawSprite() {
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), NULL, NULL, &Position, color);

	sprite->End();
}

void Object::DrawSprite(RECT* text_rec) {
	D3DXVECTOR3 Position;
	Position.x = position.x;
	Position.y = position.y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TextureIndex), text_rec, NULL, &Position, color);

	sprite->End();
}

void Object::SetObjectData(Vector2D pos, float wid, float hei)
{
	position = pos;
	width = wid;
	height = hei;
	isLive = true;
}

void Object::SetPosition(Vector2D pos)
{
	position = pos;
}

void Object::SetMoveX(float x)
{
	move.x = x;
}


void Object::SetMoveY(float y)
{
	move.y = y;
}

void Object::SetWidth(float wid)
{
	width = wid;
}

void Object::SetHeight(float hei)
{
	height = hei;
}

void Object::SetLiveFlag(bool flag)
{
	isLive = flag;
}

void Object::SetTextureIndex(int index) {
	TextureIndex = index;
}

void Object::SetPositionX(float x) {
	position.x = x;
}

void Object::SetPositionY(float y) {
	position.y = y;
}

void Object::SetCircleCollision(Circle objCollision) {
	g_CircleCollision = objCollision;
}

void Object::SetCircleCollisionX(float x) {
	g_CircleCollision.cx = x;
}

void Object::SetCircleCollisionY(float y) {
	g_CircleCollision.cy = y;
}

Vector2D Object::GetPosition() {
	return position;
}

float Object::GetWidth() {
	return width;
}

float Object::GetHeight() {
	return height;
}

bool Object::GetLiveFlag() {
	return isLive;
}

int Object::GetTextureIndex() {
	return TextureIndex;
}

Circle* Object::GetCircleCollision() {
	return &g_CircleCollision;
}

Object::~Object()
{

}

void Object::Sprite_Uninit() {
	sprite->Release();
}

void Object::SetSpriteColor(D3DCOLOR Rgba) {
	color = Rgba;
}