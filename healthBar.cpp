//==================================================
//  HPバークラス [healthBar.cpp]        Autor:ロ
//==================================================
#include "healthBar.h"
#include "texture.h"
#include "sprite.h"

// 静的メンバ変数
//==================================================
LPD3DXSPRITE Healthbar::sprite;
D3DCOLOR Healthbar::color;
D3DXVECTOR3 Healthbar::Position;
RECT Healthbar::text_rec;
float Healthbar::oldHealth;
float Healthbar::percent;

// 初期化処理
//==================================================
void Healthbar::Healthbar_Init() {
	D3DXCreateSprite(g_d3dDevice, &sprite);
	color = D3DCOLOR_ARGB(255, 255, 255, 255);
	oldHealth = HEALTHBAR_TOTAL;
	percent = 1.0f;
}

//描画処理
//==================================================
void Healthbar::Healthbar_Draw(float x, float y, int nowHealth)
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

//終了処理
//==================================================
void Healthbar::Healthbar_Uninit() {
	sprite->Release();
}