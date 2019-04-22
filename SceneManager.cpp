//==================================================
//  �V�[���̃}�l�[�W���[�N���X [SceneManager.cpp]        Autor:��
//==================================================
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"

//�ÓI�ϐ�
//==================================================
BaseScene *SceneManager::m_pScene = NULL;
int SceneManager::NewScore = 0;
int SceneManager::OldScore = 0;

//��ʃV�[������
//==================================================
void SceneManager::ChangeScene(GameStatus scene) {

	//�����O��̃X�e�[�W���̂�����Ȃ����
	if (m_pScene != NULL) {
		delete m_pScene;
		m_pScene = NULL;
	}

	switch (scene) {					//�����̃V�[��
	case GameStatus::TITLE:
		m_pScene = new TitleScene();      //�^�C�g���V�[�������݂̃V�[���ɂ���
		break;
	case GameStatus::GAME:
		m_pScene = new GameScene();       //�Q�[���V�[�������݂̃V�[���ɂ���
		break;
	case GameStatus::RESULT:
		m_pScene = new EndScene();		//���U���g�V�[�������݂̃V�[���ɂ���
		break;
	default:
		break;
	}

	//�f�o�C�X�����Z�b�g����
	ResetDevice();
}

//�X�V����
//==================================================
void SceneManager::Update() {
	m_pScene->Update();
}

//�`�揈��
//==================================================
void SceneManager::Draw() {
	m_pScene->Draw();
}

//�O��̃f�o�C�X����
//==================================================
void SceneManager::LostDevice() {
	m_pScene->LostDevice();
}

//�f�o�C�X�����Z�b�g����
//==================================================
void SceneManager::ResetDevice() {
	m_pScene->ResetDevice();
}

//�v���[���[�̃X�R�[�A��ݒ肷��
//==================================================
void SceneManager::SetEndScore(int s) {
	NewScore = s;

	if (NewScore > OldScore) {
		OldScore = NewScore;
	}
}

//�v���[���[�̃X�R�[�A���Q�b�g����
//==================================================
int SceneManager::GetEndScore(void) {
	return NewScore;
}

//���܂ōō��̃X�R�[�A�����
//==================================================
int SceneManager::GetEndScoreBest(void) {
	return OldScore;
}