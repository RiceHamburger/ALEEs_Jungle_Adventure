#include <d3d9.h>
#include "number.h"
#include "texture.h"
#include "sprite.h"
#include "direct3d_setup.h"

static LPD3DXSPRITE sprite;
static D3DCOLOR color;
static D3DXVECTOR3 Position;
static RECT text_rec;
static LPDIRECT3DDEVICE9 g_pD3DDevice;

void Number_Init() {
	g_pD3DDevice = MyDirect3D_GetDevice();
	D3DXCreateSprite(g_pD3DDevice, &sprite);
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void Number_Draw(float x, float y, int n)
{
	Position.x = x;
	Position.y = y;
	Position.z = 0;

	text_rec.left = NUMBER_WIDTH * n;
	text_rec.top = 0;
	text_rec.right = text_rec.left + NUMBER_WIDTH;
	text_rec.bottom = text_rec.top + NUMBER_HEIGHT;

	if (n < 0 || n > 9) return;
	/*Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	Sprite_Draw(NUMBER, x, y, NUMBER_WIDTH * n, 0, NUMBER_WIDTH, NUMBER_HEIGHT);*/

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(NUMBER), &text_rec, NULL, &Position, color);

	sprite->End();
}

void Number_Uninit() {
	sprite->Release();
}