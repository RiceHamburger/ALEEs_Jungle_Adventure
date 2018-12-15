#include <d3d9.h>
#include "healthBar.h"
#include "texture.h"
#include "sprite.h"
#include "direct3d_setup.h"

static LPD3DXSPRITE sprite;
static D3DCOLOR color;
static D3DXVECTOR3 Position;
static RECT text_rec;
static LPDIRECT3DDEVICE9 g_pD3DDevice;

//bloodbar
static float oldHealth;
static float percent;

void Healthbar_Init() {
	g_pD3DDevice = MyDirect3D_GetDevice();
	D3DXCreateSprite(g_pD3DDevice, &sprite);
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	oldHealth = HEALTHBAR_TOTAL;
	percent = 1.0f;
}

void Healthbar_Draw(float x, float y, int nowHealth)
{
	//show percent
	if (nowHealth != oldHealth) {
		if (nowHealth < oldHealth) {
			oldHealth -= (oldHealth - nowHealth);
			if (oldHealth <= 0) {
				oldHealth = 0;
			}
		}
		else {
			oldHealth += (nowHealth - oldHealth);
			if (oldHealth >= HEALTHBAR_TOTAL) {
				oldHealth = HEALTHBAR_TOTAL;
			}
		}
		percent = oldHealth / HEALTHBAR_TOTAL;
	}

	Position.x = x;
	Position.y = y;
	Position.z = 0;

	text_rec.left = 0;
	text_rec.top = 0;
	text_rec.right = text_rec.left + HEALTHBAR_WIDTH * percent;
	text_rec.bottom = text_rec.top + HEALTHBAR_HEIGHT;

	sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	sprite->Draw(Texture_GetTexture(HEALTH_BAR), &text_rec, NULL, &Position, color);

	sprite->End();
}

void Healthbar_Uninit() {
	sprite->Release();
}