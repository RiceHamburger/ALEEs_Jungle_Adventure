//==================================================
//  シーンのマネージャークラス [SceneManager.cpp]        Autor:ロ
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

	switch (scene) {          //引数のシーン
	case GameStatus::TITLE:
		m_pScene = new TitleScene();      //タイトルシーンを現在のシーンにする
		break;
	case GameStatus::GAME:
		m_pScene = new GameScene();       //ゲームシーンを現在のシーンにする
		break;
	case GameStatus::RESULT:
		m_pScene = new EndScene();		//リザルトシーンを現在のシーンにする
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