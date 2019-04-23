//==================================================
//  水の管理者クラス [WaterManager.cpp]        Autor:ロ
//==================================================
#include "WaterManager.h"

// 静的メンバ変数
//==================================================
D3DXVECTOR3 WaterManager::water_position[WATER_MAX] = {
	{ 118,202,0 },
	{ 958,383,0 },
	{ 1438,802,0 },
	{ 2578,922,0 }
};
WaterStain WaterManager::waterStain[WATER_MAX];

// 初期化処理
//==================================================
void WaterManager::Water_Manager_Init(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].SetPosition(water_position[i]);
		waterStain[i].InitSprite();
	}
}

//更新処理
//==================================================
void WaterManager::Water_Manager_Update(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].UpdateSprite();
	}
}

//描画処理
//==================================================
void WaterManager::Water_Manager_Draw(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].DrawSprite();
	}
}

//終了処理
//==================================================
void WaterManager::Water_Manager_Uninit(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].Sprite_Uninit();
	}
}