//==================================================
//  Item UI‚ÌƒNƒ‰ƒX [ItemUI.cpp]        Autor:ƒ
//==================================================

#include "texture.h"
#include "ItemUI.h"

LPD3DXSPRITE ItemUI::sprite;
D3DXVECTOR3 ItemUI::Position;

void ItemUI::itemUI_Draw(float x, float y) {

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TONICGUN), NULL, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

void ItemUI::itemUI_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

void ItemUI::itemUI_Uninit() {
	sprite->Release();
}