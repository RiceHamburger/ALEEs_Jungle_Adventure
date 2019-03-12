#include "texture.h"
#include "water_stain.h"
#include "D3Dsetup.h"

WaterStain::WaterStain()
{
	Position = { 0,0,0 };
	textureX = 0;
	textureY = 0;
	textureX_index = 0;
	textureY_index = 0;
	aniTime = WATER_ANI_TIME;
	sprite = NULL;
	water_rec = { 0,0,0,0 };
}

WaterStain::~WaterStain()
{

}

void WaterStain::UpdateSprite() {
	aniTime--;
	if (aniTime <= 0) {

		textureX_index++;
		if (textureX_index >= WATER_TEXTURE_MAX) {
			textureX_index = 0;

			textureY_index++;
			if (textureY_index >= WATER_TEXTURE_MAX) {
				textureY_index = 0;
			}
		}

		textureX = WATER_WIDTH*(textureX_index % WATER_TEXTURE_MAX);
		textureY = WATER_HEIGHT*(textureY_index % WATER_TEXTURE_MAX);
		aniTime = WATER_ANI_TIME;

		water_rec.left = textureX;
		water_rec.top = textureY;
		water_rec.right = water_rec.left + WATER_WIDTH;
		water_rec.bottom = water_rec.top + WATER_HEIGHT;
	}
}

void WaterStain::DrawSprite() {
	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(WATERSTAIN), &water_rec, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

void WaterStain::InitSprite() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
}

void WaterStain::Sprite_Uninit() {
	sprite->Release();
}

void WaterStain::SetPosition(D3DXVECTOR3 p_water) {
	Position = p_water;
}

void WaterStain::SetNowTexture(int t_X, int t_Y) {
	textureX_index = t_X;
	textureY_index = t_Y;
}