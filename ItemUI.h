//==================================================
//  Item UIÇÃÉNÉâÉX [ItemUI.h]        Autor:Éç
//==================================================

#ifndef ITEMUI_H_
#define ITEMUI_H_

#include "D3Dsetup.h"

#define ITEMUI_X (300.0f)
#define ITEMUI_Y (35.0f)

class ItemUI
{
public:
	static void itemUI_Draw(float x, float y);
	static void itemUI_Init();
	static void itemUI_Uninit();
private:
	static LPD3DXSPRITE sprite;
	static D3DXVECTOR3 Position;
};

#endif // ITEMUI_H_