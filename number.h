//==================================================
//  ”šƒNƒ‰ƒX [Number.h]        Autor:ƒ
//==================================================

#ifndef NUMBER_H_
#define NUMBER_H_

#include "D3Dsetup.h"

#define NUMBER_WIDTH	(32)
#define NUMBER_HEIGHT	(32)

class Number {
public:
	// 0 <= n <= 9
	static void Number_Draw(float x, float y, int n);
	static void Number_Init();
	static void Number_Uninit();
private:
	static LPD3DXSPRITE sprite;
	static D3DCOLOR color;
	static D3DXVECTOR3 Position;
	static RECT text_rec;
};

#endif // NUMBER_H_