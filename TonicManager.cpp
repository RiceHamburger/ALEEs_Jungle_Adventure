//==================================================
//  �A�C�e���Ǘ��҃N���X [TonicManager.cpp]        Autor:��
//==================================================
#include "TonicManager.h"
#include <time.h>

// �ÓI�����o�ϐ�
//==================================================
Tonic TonicManager::g_tonic[TONIC_MAX];
Tonic TonicManager::g_tonicGun;

// ����������
//==================================================
void TonicManager::Tonic_Manager_Init(void) {
	for (int i = 0;i < TONIC_MAX - 1;i++) {
		g_tonic[i].InitTonic({ 0.0f, 0.0f }, TONIC, HPUP);
		g_tonic[i].InitSprite();
		g_tonic[i].SetLiveFlag(false);
	}

	g_tonic[TONIC_MAX - 1].InitTonic({ 1468.0f, 742.0f }, TONICGUN, SHOOTGUN);
	g_tonic[TONIC_MAX - 1].InitSprite();
	g_tonic[TONIC_MAX - 1].SetLiveFlag(false);

	srand((unsigned)time(NULL));
}

//�X�V����
//==================================================
void TonicManager::Tonic_Manager_Update(void) {
	/*for (int i = 0;i < TONIC_MAX;i++) {
	if (g_tonic[i].GetLiveFlag()) {
	g_tonic[i].ExplosionActive();
	}
	}*/
}

//�`�揈��
//==================================================
void TonicManager::Tonic_Manager_Draw(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			g_tonic[i].DrawSprite();
		}
	}
}

//�I������
//==================================================
void TonicManager::Tonic_Manager_Uninit(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		g_tonic[i].Sprite_Uninit();
	}
}

//�A�C�e����������
//==================================================
void TonicManager::Tonic_Create(float x, float y) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (!g_tonic[i].GetLiveFlag()) {
			g_tonic[i].SetPositionX(x);
			g_tonic[i].SetPositionY(y);
			g_tonic[i].resetCollision();
			g_tonic[i].SetLiveFlag(true);
			break;
		}
	}
}

//�A�C�e�����s�`�F�b�N����
//==================================================
bool TonicManager::Tonic_IsEnable(void) {
	for (int i = 0;i < TONIC_MAX;i++) {
		if (g_tonic[i].GetLiveFlag()) {
			return true;
		}
	}
	return false;
}

//�A�C�e���̃|�C���^�����
//==================================================
Tonic* TonicManager::TonicMgrGetTonic() {
	return g_tonic;
}

//�e�A�C�e����������
//==================================================
void TonicManager::Tonic_CreateGun(float x, float y) {
	if (!g_tonic[TONIC_MAX - 1].GetLiveFlag()) {
		g_tonic[TONIC_MAX - 1].SetPositionX(x);
		g_tonic[TONIC_MAX - 1].SetPositionY(y);
		g_tonic[TONIC_MAX - 1].resetCollision();
		g_tonic[TONIC_MAX - 1].SetLiveFlag(true);
	}
}