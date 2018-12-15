#include "tonic_Manager.h"
#include <time.h>

Tonic g_tonic[TONIC_MAX];

void Tonic_Manager_Init(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		g_tonic[i].InitTonic({ 0.0f, 0.0f }, TONIC);
		g_tonic[i].InitSprite();
	}

	srand((unsigned)time(NULL));
}

void Tonic_Manager_Update(void) {
	/*for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			g_tonic[i].ExplosionActive();
		}
	}*/
}

void Tonic_Manager_Draw(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			g_tonic[i].DrawSprite();
		}
	}
}

void Tonic_Manager_Uninit(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		g_tonic[i].Sprite_Uninit();
	}
}

void Tonic_Create(float x, float y) {
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

bool Tonic_IsEnable(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

Tonic *TonicMgrGetTonic() {
	return g_tonic;
}