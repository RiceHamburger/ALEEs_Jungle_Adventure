//==================================================
//  爆発効果管理者クラス [ExplosionManager.cpp]        Autor:ロ
//==================================================
#include "ExplosionManager.h"

//explosion配列を宣言する
Explosion ExplosionManager::explosion[EXPLOSION_MAX];

// 初期化処理
//==================================================
void ExplosionManager::Explosion_Manager_Init(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		explosion[i].InitExplosion({ 0.0f, 0.0f }, EXPLOSION, EXPLOSION_PIC_NUM, EXPLOSION_PIC_NUM);
		explosion[i].InitSprite();
	}
}

//更新処理
//==================================================
void ExplosionManager::Explosion_Manager_Update(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		if (explosion[i].GetLiveFlag()) {
			explosion[i].ExplosionActive();
		}
	}
}

//描画処理
//==================================================
void ExplosionManager::Explosion_Manager_Draw(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		if (explosion[i].GetLiveFlag()) {
			explosion[i].DrawSprite(explosion[i].GetRect());
		}
	}
}

//廃棄処理
//==================================================
void ExplosionManager::Explosion_Manager_Uninit(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		explosion[i].Sprite_Uninit();
	}
}

//生成処理
//==================================================
void ExplosionManager::Explosion_Create(float x, float y) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		if (!explosion[i].GetLiveFlag()) {
			explosion[i].SetPositionX(x);
			explosion[i].SetPositionY(y);
			explosion[i].SetLiveFlag(true);
			break;
		}
	}
}