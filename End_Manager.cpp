#include "End_Manager.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "game.h"
#include "common.h"
#include "fade.h"
#include "sound.h"

#include "number.h"

static bool gameToEndFadeIn = false;
static bool endToStartFadeInOut = false;
static bool endFadeOver = false;

static int endShowScore = 0;
static int endShowScoreBest = 0;


void EndInit(void) {
	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
	gameToEndFadeIn = true;
	endToStartFadeInOut = false;
	endFadeOver = false;
	PlaySound(SOUND_LABEL_BGM003);
}

void EndUpdate(void) {
	//if fading return
	if (Fade_IsFade()) {
		return;
	}

	//gameToEndFadeIn over,z press fadeout start
	if (gameToEndFadeIn) {
		if (Keyboard_IsTrigger(DIK_SPACE) || Xinput_IsTrigger(XINPUT_GAMEPAD_B)) {
			PlaySound(SOUND_LABEL_SE_KEYDOWN);
			StopSound(SOUND_LABEL_BGM003);
			//タイトル画面からゲーム画面に
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 255));
			gameToEndFadeIn = false;
			endToStartFadeInOut = true;
		}
	}else if (!gameToEndFadeIn && !Fade_IsFade() && endToStartFadeInOut) {
		Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
		endFadeOver = true;
		endToStartFadeInOut = false;
	}
	
	if(endFadeOver && !Fade_IsFade()) {
		
		GameSceneChange(Scene_Title);
	}
}

void EndDraw(void) {
	if (endFadeOver && !endToStartFadeInOut) {
		Sprite_Draw(TITLE, (SCREEN_WIDTH - Texture_GetWidth(TITLE)) / 2, (SCREEN_HEIGHT - Texture_GetHeight(TITLE)) / 3);
	}
	else {
		Sprite_Draw(END, (SCREEN_WIDTH - Texture_GetWidth(END)) / 2, (SCREEN_HEIGHT - Texture_GetHeight(END)) / 3);


		endShowScore = GetEndScore();
		endShowScoreBest = GetEndScoreBest();
		//now score
		for (int i = 0; i < 5; i++) {
			int n = endShowScore % 10;
			endShowScore /= 10;

			Sprite_Draw(NUMBER_END, END_SCORE_X + NUMBER_WIDTH * (5 - (i + 1)), END_SCORE_Y_NOW, NUMBER_WIDTH * n, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
		}
		
		//best score
		for (int i = 0; i < 5; i++) {
			int n = endShowScoreBest % 10;
			endShowScoreBest /= 10;

			Sprite_Draw(NUMBER_END, END_SCORE_X + NUMBER_WIDTH * (5 - (i + 1)), END_SCORE_Y_OLD, NUMBER_WIDTH * n, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
		}
	}
}

void EndUninit(void) {

}