//==================================================
//  �������ʊǗ��҃N���X [ExplosionManager.cpp]        Autor:��
//==================================================
#include "ExplosionManager.h"

//explosion�z���錾����
Explosion ExplosionManager::explosion[EXPLOSION_MAX];

// ����������
//==================================================
void ExplosionManager::Explosion_Manager_Init(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		explosion[i].InitExplosion({ 0.0f, 0.0f }, EXPLOSION, EXPLOSION_PIC_NUM, EXPLOSION_PIC_NUM);
		explosion[i].InitSprite();
	}
}

//�X�V����
//==================================================
void ExplosionManager::Explosion_Manager_Update(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		if (explosion[i].GetLiveFlag()) {
			explosion[i].ExplosionActive();
		}
	}
}

//�`�揈��
//==================================================
void ExplosionManager::Explosion_Manager_Draw(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		if (explosion[i].GetLiveFlag()) {
			explosion[i].DrawSprite(explosion[i].GetRect());
		}
	}
}

//�p������
//==================================================
void ExplosionManager::Explosion_Manager_Uninit(void) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		explosion[i].Sprite_Uninit();
	}
}

//��������
//==================================================
void ExplosionManager::Explosion_Create(float x, float y) {
	for (int i = 0;i < EXPLOSION_MAX;i++) {
		if (!explosion[i].GetLiveFlag()) {
			explosion[i].SetPositionX(x);
			explosion[i].SetPositionY(y);
			explosion[i].SetLiveFlag(true);
			break;
		}
	}
}