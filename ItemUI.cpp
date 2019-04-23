//==================================================
//  Item UIのクラス [ItemUI.cpp]        Autor:ロ
//==================================================
#include "texture.h"
#include "ItemUI.h"

//アイテムスプライト
LPD3DXSPRITE ItemUI::sprite;
//アイテム座標
D3DXVECTOR3 ItemUI::Position;

//描画処理
//==================================================
void ItemUI::itemUI_Draw(float x, float y) {

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TONICGUN), NULL, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

// 初期化処理
//==================================================
void ItemUI::itemUI_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

//終了処理
//==================================================
void ItemUI::itemUI_Uninit() {
	sprite->Release();
}