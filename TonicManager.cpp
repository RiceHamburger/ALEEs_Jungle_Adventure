//==================================================
//  アイテム管理者クラス [TonicManager.cpp]        Autor:ロ
//==================================================
#include "TonicManager.h"
#include <time.h>

// 静的メンバ変数
//==================================================
Tonic TonicManager::g_tonic[TONIC_MAX];
Tonic TonicManager::g_tonicGun;

// 初期化処理
//==================================================
void TonicManager::Tonic_Manager_Init(void) {
	for (int i = 0;i < TONIC_MAX - 1;i++) {
		g_tonic[i].InitTonic({ 0.0f, 0.0f }, TONIC, HPUP);
		g_tonic[i].InitSprite();
		g_tonic[i].SetLiveFlag(false);
	}

	g_tonic[TONIC_MAX - 1].InitTonic({ 1468.0f, 742.0f }, TONICGUN, SHOOTGUN);
	g_tonic[TONIC_MAX - 1].InitSprite();
	g_tonic[TONIC_MAX - 1].SetLiveFlag(false);

	srand((unsigned)time(NULL));
}

//更新処理
//==================================================
void TonicManager::Tonic_Manager_Update(void) {
	/*for (int i = 0;i < TONIC_MAX;i++) {
	if (g_tonic[i].GetLiveFlag()) {
	g_tonic[i].ExplosionActive();
	}
	}*/
}

//描画処理
//==================================================
void TonicManager::Tonic_Manager_Draw(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			g_tonic[i].DrawSprite();
		}
	}
}

//終了処理
//==================================================
void TonicManager::Tonic_Manager_Uninit(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		g_tonic[i].Sprite_Uninit();
	}
}

//アイテム生成処理
//==================================================
void TonicManager::Tonic_Create(float x, float y) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (!g_tonic[i].GetLiveFlag()) {
			g_tonic[i].SetPositionX(x);
			g_tonic[i].SetPositionY(y);
			g_tonic[i].resetCollision();
			g_tonic[i].SetLiveFlag(true);
			break;
		}
	}
}

//アイテム実行チェック処理
//==================================================
bool TonicManager::Tonic_IsEnable(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

//アイテムのポインタを取る
//==================================================
Tonic* TonicManager::TonicMgrGetTonic() {
	return g_tonic;
}

//銃アイテム生成処理
//==================================================
void TonicManager::Tonic_CreateGun(float x, float y) {
	if (!g_tonic[TONIC_MAX - 1].GetLiveFlag()) {
		g_tonic[TONIC_MAX - 1].SetPositionX(x);
		g_tonic[TONIC_MAX - 1].SetPositionY(y);
		g_tonic[TONIC_MAX - 1].resetCollision();
		g_tonic[TONIC_MAX - 1].SetLiveFlag(true);
	}
}