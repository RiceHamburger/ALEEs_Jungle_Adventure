//==================================================
//  �^�C�g����ʂ̃N���X [TitleScene.cpp]     Autor:��
//==================================================

#include "TitleScene.h"
#include "texture.h"
#include "D3DInput.h"
#include "SceneManager.h"
#include "sound.h"
#include "fade.h"

TitleScene::TitleScene() {
	m_UI = new Sprite();

	countTime = TITLE_TIME;
	btn_alpha = TITLETEXT_ALPHA;
	startFadeInOut = false;
	PlaySound(SOUND_LABEL_BGM000);

	g_Fade->init();
}

TitleScene::~TitleScene() {
	
}

void TitleScene::Update() {
	static float timeElapsed = 0.0f;
	//timeElapsed += dt;

	if (!startFadeInOut) {
		if (gDInput->keyIsTrigger(DIK_SPACE)) {
			PlaySound(SOUND_LABEL_SE_KEYDOWN);

			//�^�C�g����ʂ���Q�[����ʂ�
			//20�͉�
			g_Fade->Fade_Start(true, 500, D3DCOLOR_RGBA(0, 0, 0, 255));

			//�t�F�C�g�C���J�n
			startFadeInOut = true;
		}
	}

	if (startFadeInOut && !g_Fade->Fade_IsFade()) {
		//�^�C�g���̉������~�߂�
		StopSound(SOUND_LABEL_BGM000);

		delete m_UI;

		//�t�F�C�g�C���I��
		startFadeInOut = false;

		//�Q�[����ʂɂ���
		SceneManager::ChangeScene(SceneManager::GAME);

	}

	//press btn shining
	//if (timeElapsed >= 0.1f) {
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

		//timeElapsed = 0.0f;
	//}
}

void TitleScene::Draw() {
	m_UI->Sprite_Draw(TITLE, (SCREEN_WIDTH - Texture_GetWidth(TITLE)) / 2, (SCREEN_HEIGHT - Texture_GetHeight(TITLE)) / 3);
	m_UI->Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, btn_alpha));
	m_UI->Sprite_Draw(TITLEBTN, (SCREEN_WIDTH - Texture_GetWidth(TITLEBTN)) / 2, SCREEN_HEIGHT / 2 + 280);
	m_UI->Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void TitleScene::LostDevice() {
	
}

void TitleScene::ResetDevice() {

}