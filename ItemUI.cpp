//==================================================
//  Item UI�̃N���X [ItemUI.cpp]        Autor:��
//==================================================
#include "texture.h"
#include "ItemUI.h"

//�A�C�e���X�v���C�g
LPD3DXSPRITE ItemUI::sprite;
//�A�C�e�����W
D3DXVECTOR3 ItemUI::Position;

//�`�揈��
//==================================================
void ItemUI::itemUI_Draw(float x, float y) {

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(TONICGUN), NULL, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

// ����������
//==================================================
void ItemUI::itemUI_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

//�I������
//==================================================
void ItemUI::itemUI_Uninit() {
	sprite->Release();
}