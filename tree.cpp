#include "tree.h"
#include "texture.h"

TREE::TREE() {

}
TREE::~TREE() {
}
void TREE::InitTREE(D3DXVECTOR3 Position) {
	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	D3DXCreateSprite(g_pD3DDevice, &sprite);
	position = Position;
	color = D3DCOLOR_ARGB(255, 255, 255, 255);

	collision_rec.left = position.x + 20;
	collision_rec.top = position.y + 20;
	collision_rec.right = collision_rec.left + TREE_WIDTH - 40;
	collision_rec.bottom = collision_rec.top + TREE_HEIGHT - 40;
}
void TREE::DrawTREE() {
	RECT text_rec;
	text_rec.left = 0;
	text_rec.top = 0;
	text_rec.right = text_rec.left + TREE_WIDTH;
	text_rec.bottom = text_rec.top + TREE_HEIGHT;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TREE_TEXTURE), &text_rec, NULL, &position, color);

	sprite->End();
}
void TREE::UninitTREE() {
	sprite->Release();
}

RECT TREE::GetCollision() {
	return collision_rec;
}