#include <d3d9.h>
#include "direct3d_setup.h"
#include "texture.h"
#include "playerUI.h"

static LPD3DXSPRITE sprite;
static D3DXVECTOR3 Position;
static LPDIRECT3DDEVICE9 g_pD3DDevice;

void playerUI_Draw(float x, float y) {

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(PLAYER_UI), NULL, NULL, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->End();
}

void playerUI_Init() {
	g_pD3DDevice = MyDirect3D_GetDevice();
	D3DXCreateSprite(g_pD3DDevice, &sprite);
}

void playerUI_Uninit() {
	sprite->Release();
}