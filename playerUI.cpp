//==================================================
//  player UI‚ÌƒNƒ‰ƒX [PlayerUI.cpp]        Autor:ƒ
//==================================================

#include "texture.h"
#include "PlayerUI.h"

LPD3DXSPRITE PlayerUI::sprite;
D3DXVECTOR3 PlayerUI::Position;

void PlayerUI::playerUI_Draw(float x, float y) {

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(PLAYER_UI), NULL, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

void PlayerUI::playerUI_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

void PlayerUI::playerUI_Uninit() {
	sprite->Release();
}