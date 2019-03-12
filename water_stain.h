#ifndef WATER_STAIN_H
#define WATER_STAIN_H

#include "common.h"
#include "D3Dsetup.h"

#define WATER_WIDTH	(64)
#define WATER_HEIGHT (64)
#define WATER_MAX	(4)
#define WATER_TEXTURE_MAX	(3)
#define WATER_ANI_TIME	(200)

class WaterStain {
private:
	int textureX;
	int textureY;
	int textureX_index;
	int textureY_index;
	int aniTime;

	D3DXVECTOR3 Position;
	RECT water_rec;

	//camera
	LPD3DXSPRITE sprite;
public:
	WaterStain();
	~WaterStain();

	void UpdateSprite();
	void DrawSprite();
	void InitSprite();
	void Sprite_Uninit();
	void SetPosition(D3DXVECTOR3 p_water);
	void SetNowTexture(int t_X, int t_Y);
};

#endif