//==================================================
//  ���̊Ǘ��҃N���X [WaterManager.cpp]        Autor:��
//==================================================
#include "WaterManager.h"

// �ÓI�����o�ϐ�
//==================================================
D3DXVECTOR3 WaterManager::water_position[WATER_MAX] = {
	{ 118,202,0 },
	{ 958,383,0 },
	{ 1438,802,0 },
	{ 2578,922,0 }
};
WaterStain WaterManager::waterStain[WATER_MAX];

// ����������
//==================================================
void WaterManager::Water_Manager_Init(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].SetPosition(water_position[i]);
		waterStain[i].InitSprite();
	}
}

//�X�V����
//==================================================
void WaterManager::Water_Manager_Update(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].UpdateSprite();
	}
}

//�`�揈��
//==================================================
void WaterManager::Water_Manager_Draw(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].DrawSprite();
	}
}

//�I������
//==================================================
void WaterManager::Water_Manager_Uninit(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].Sprite_Uninit();
	}
}