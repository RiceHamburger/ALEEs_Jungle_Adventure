//==================================================
//  タイトル画面のクラス [EndScene.cpp]     Autor:ロ
//==================================================

#include "EndScene.h"
#include "GameScene.h"
#include "common.h"
#include "fade.h"
#include "texture.h"
#include "D3DInput.h"
#include "SceneManager.h"
#include "sound.h"
#include "Number.h"

#define END_SCORE_X (440)
#define END_SCORE_Y_NOW (339)
#define END_SCORE_Y_OLD (499)

// 静的メンバ変数
//==================================================
bool EndScene::gameToEndFadeIn = false;
bool EndScene::endToStartFadeInOut = false;
bool EndScene::endFadeOver = false;
int EndScene::endShowScore = 0;
int EndScene::endShowScoreBest = 0;

EndScene::EndScene() {
	m_UI = new Sprite();
	m_UI->Sprite_Initialize();

	g_Fade->Fade_Start(false, 500, D3DCOLOR_RGBA(0, 0, 0, 0));
	gameToEndFadeIn = true;
	endToStartFadeInOut = false;
	endFadeOver = false;
	PlaySound(SOUND_LABEL_BGM003);
}

EndScene::~EndScene() {
	
}

void EndScene::Update() {
	//if fading return
	if (g_Fade->Fade_IsFade()) {
		return;
	}

	//gameToEndFadeIn over,z press fadeout start
	if (gameToEndFadeIn) {
		if (gDInput->keyIsTrigger(DIK_SPACE)) {
			PlaySound(SOUND_LABEL_SE_KEYDOWN);
			StopSound(SOUND_LABEL_BGM003);
			//タイトル画面からゲーム画面に
			g_Fade->Fade_Start(true, 500, D3DCOLOR_RGBA(0, 0, 0, 255));
			gameToEndFadeIn = false;
			endToStartFadeInOut = true;
		}
	}
	else if (!gameToEndFadeIn && !g_Fade->Fade_IsFade() && endToStartFadeInOut) {
		g_Fade->Fade_Start(false, 500, D3DCOLOR_RGBA(0, 0, 0, 0));
		endFadeOver = true;
		endToStartFadeInOut = false;
	}

	if (endFadeOver && !g_Fade->Fade_IsFade()) {
		m_UI->Sprite_Finalize();
		delete m_UI;
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void EndScene::Draw() {
	if (endFadeOver && !endToStartFadeInOut) {
		m_UI->Sprite_Draw(TITLE, (SCREEN_WIDTH - Texture_GetWidth(TITLE)) / 2, (SCREEN_HEIGHT - Texture_GetHeight(TITLE)) / 3);
	}
	else {
		m_UI->Sprite_Draw(END, (SCREEN_WIDTH - Texture_GetWidth(END)) / 2, (SCREEN_HEIGHT - Texture_GetHeight(END)) / 3);


		endShowScore = SceneManager::GetEndScore();
		endShowScoreBest = SceneManager::GetEndScoreBest();
		//now score
		for (int i = 0; i < 5; i++) {
			int n = endShowScore % 10;
			endShowScore /= 10;

			m_UI->Sprite_Draw(NUMBER_END, END_SCORE_X + NUMBER_WIDTH * (5 - (i + 1)), END_SCORE_Y_NOW, NUMBER_WIDTH * n, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
		}

		//best score
		for (int i = 0; i < 5; i++) {
			int n = endShowScoreBest % 10;
			endShowScoreBest /= 10;

			m_UI->Sprite_Draw(NUMBER_END, END_SCORE_X + NUMBER_WIDTH * (5 - (i + 1)), END_SCORE_Y_OLD, NUMBER_WIDTH * n, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
		}
	}
}

void EndScene::LostDevice() {
	
}

void EndScene::ResetDevice() {

	
}