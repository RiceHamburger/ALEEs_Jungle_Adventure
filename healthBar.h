#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_
#include "D3Dsetup.h"

#define HEALTHBAR_WIDTH	(256)//2“IŽŸ•û
#define HEALTHBAR_HEIGHT (16)
#define HEALTHBAR_TOTAL	(200)
#define HEALTHBAR_X (98.0f)
#define HEALTHBAR_Y (60.0f)

class Healthbar {
public:
	//static const int HEALTHBAR_WIDTH = 256;

	static void Healthbar_Draw(float x, float y, int nowHealth);
	static void Healthbar_Init();
	static void Healthbar_Uninit();
private:
	static LPD3DXSPRITE sprite;
	static D3DCOLOR color;
	static D3DXVECTOR3 Position;
	static RECT text_rec;

	//bloodbar
	static float oldHealth;
	static float percent;
};

#endif // HEALTHBAR_H_