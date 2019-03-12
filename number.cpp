//==================================================
//  êîéöÉNÉâÉX [Number.cpp]        Autor:Éç
//==================================================

#include <d3d9.h>
#include "Number.h"
#include "texture.h"
#include "sprite.h"

LPD3DXSPRITE Number::sprite;
D3DCOLOR Number::color;
D3DXVECTOR3 Number::Position;
RECT Number::text_rec;

void Number::Number_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void Number::Number_Draw(float x, float y, int n)
{
	Position.x = x;
	Position.y = y;
	Position.z = 0;

	text_rec.left = NUMBER_WIDTH * n;
	text_rec.top = 0;
	text_rec.right = text_rec.left + NUMBER_WIDTH;
	text_rec.bottom = text_rec.top + NUMBER_HEIGHT;

	if (n < 0 || n > 9) return;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(NUMBER), &text_rec, NULL, &Position, color);

	sprite->End();
}

void Number::Number_Uninit() {
	sprite->Release();
}