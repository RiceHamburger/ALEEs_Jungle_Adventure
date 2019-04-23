//==================================================
//  player UIのクラス [PlayerUI.cpp]        Autor:ロ
//==================================================
#include "texture.h"
#include "PlayerUI.h"

// 静的メンバ変数
//==================================================
LPD3DXSPRITE PlayerUI::sprite;
D3DXVECTOR3 PlayerUI::Position;

//描画処理
//==================================================
void PlayerUI::playerUI_Draw(float x, float y) {

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(PLAYER_UI), NULL, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

// 初期化処理
//==================================================
void PlayerUI::playerUI_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

//終了処理
//==================================================
void PlayerUI::playerUI_Uninit() {
	sprite->Release();
}