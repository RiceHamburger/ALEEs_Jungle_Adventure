//==================================================
//  アイテム管理者クラス [TonicManager.h]        Autor:ロ
//==================================================

#ifndef TONICMANAGER_H
#define TONICMANAGER_H

#include "tonic.h"

class TonicManager {
public:
	static void Tonic_Manager_Init(void);
	static void Tonic_Manager_Update(void);
	static void Tonic_Manager_Draw(void);
	static void Tonic_Manager_Uninit(void);

	static void Tonic_Create(float x, float y);
	static bool Tonic_IsEnable(void);
	static Tonic *TonicMgrGetTonic(void);

	static void Tonic_CreateGun(float x, float y);
private:
	static Tonic g_tonic[TONIC_MAX];
	static Tonic g_tonicGun;
};

#endif