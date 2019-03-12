//==================================================
//  player UIÇÃÉNÉâÉX [PlayerUI.h]        Autor:Éç
//==================================================

#ifndef PLAYERUI_H_
#define PLAYERUI_H_

#include "D3Dsetup.h"

#define PLAYERUI_X (30.0f)
#define PLAYERUI_Y (20.0f)

class PlayerUI {
public:
	static void playerUI_Draw(float x, float y);
	static void playerUI_Init();
	static void playerUI_Uninit();
private:
	static LPD3DXSPRITE sprite;
	static D3DXVECTOR3 Position;
};

#endif // PLAYERUI_H_