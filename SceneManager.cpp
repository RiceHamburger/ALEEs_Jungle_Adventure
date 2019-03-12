//==================================================
//  �V�[���̃}�l�[�W���[�N���X [SceneManager.cpp]        Autor:��
//==================================================
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"

BaseScene *SceneManager::m_pScene = NULL;

int SceneManager::NewScore = 0;
int SceneManager::OldScore = 0;

void SceneManager::ChangeScene(GameStatus scene) {

	if (m_pScene != NULL) {
		delete m_pScene;
		m_pScene = NULL;
	}

	switch (scene) {          //�����̃V�[��
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

	ResetDevice();
}

void SceneManager::Update() {
	m_pScene->Update();
}

void SceneManager::Draw() {
	m_pScene->Draw();
}

void SceneManager::LostDevice() {
	m_pScene->LostDevice();
}

void SceneManager::ResetDevice() {
	m_pScene->ResetDevice();
}

void SceneManager::SetEndScore(int s) {
	NewScore = s;

	if (NewScore > OldScore) {
		OldScore = NewScore;
	}
}

int SceneManager::GetEndScore(void) {
	return NewScore;
}

int SceneManager::GetEndScoreBest(void) {
	return OldScore;
}