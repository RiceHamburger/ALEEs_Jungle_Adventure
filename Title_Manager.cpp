#include "Title_Manager.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "game.h"
#include "common.h"

#include "fade.h"
#include "sound.h"

#define TITLE_TIME (30)
#define TITLETEXT_ALPHA (255)

static int countTime = TITLE_TIME;
static int btn_alpha = TITLETEXT_ALPHA;

static bool startFadeInOut = false;

void TitleInit(void) {
	countTime = TITLE_TIME;
	btn_alpha = TITLETEXT_ALPHA;
	startFadeInOut = false;
	PlaySound(SOUND_LABEL_BGM000);
}

void TitleUpdate(void) {

	if (!startFadeInOut) {
		//if (Keyboard_IsTrigger(DIK_SPACE) || Xinput_IsTrigger(XINPUT_GAMEPAD_B)) {
		if (Keyboard_IsTrigger(DIK_SPACE) || Xinput_IsTrigger(XINPUT_GAMEPAD_B)) {
			PlaySound(SOUND_LABEL_SE_KEYDOWN);
			//タイトル画面からゲーム画面に
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 255));
			startFadeInOut = true;
		}
	}

	if (startFadeInOut && !Fade_IsFade()) {
		StopSound(SOUND_LABEL_BGM000);
		GameSceneChange(Scene_Level_1);
		startFadeInOut = false;
	}

	//press btn shining
	countTime--;
	if (countTime <= 0) {
		if (btn_alpha == TITLETEXT_ALPHA) {
			btn_alpha = 0;
		}
		else {
			btn_alpha = TITLETEXT_ALPHA;
		}
		countTime = TITLE_TIME;
	}
}

void TitleDraw(void) {
	Sprite_Draw(TITLE, (SCREEN_WIDTH - Texture_GetWidth(TITLE)) / 2, (SCREEN_HEIGHT - Texture_GetHeight(TITLE)) / 3);
	//Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, (int)((1 + sin(count / 180.0f * D3DX_PI)) / 2 * 255)));
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, btn_alpha));
	Sprite_Draw(TITLEBTN, (SCREEN_WIDTH - Texture_GetWidth(TITLEBTN)) / 2, SCREEN_HEIGHT / 2 + 280);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void TitleUninit(void) {

}