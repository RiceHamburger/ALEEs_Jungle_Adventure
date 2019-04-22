//==================================================
//  シーンのマネージャークラス [SceneManager.cpp]        Autor:ロ
//==================================================
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "EndScene.h"

//静的変数
//==================================================
BaseScene *SceneManager::m_pScene = NULL;
int SceneManager::NewScore = 0;
int SceneManager::OldScore = 0;

//画面シーン処理
//==================================================
void SceneManager::ChangeScene(GameStatus scene) {

	//もし前回のステージものがあるなら消す
	if (m_pScene != NULL) {
		delete m_pScene;
		m_pScene = NULL;
	}

	switch (scene) {					//引数のシーン
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

	//デバイスをリセットする
	ResetDevice();
}

//更新処理
//==================================================
void SceneManager::Update() {
	m_pScene->Update();
}

//描画処理
//==================================================
void SceneManager::Draw() {
	m_pScene->Draw();
}

//前回のデバイス処理
//==================================================
void SceneManager::LostDevice() {
	m_pScene->LostDevice();
}

//デバイスをリセット処理
//==================================================
void SceneManager::ResetDevice() {
	m_pScene->ResetDevice();
}

//プレーヤーのスコーアを設定する
//==================================================
void SceneManager::SetEndScore(int s) {
	NewScore = s;

	if (NewScore > OldScore) {
		OldScore = NewScore;
	}
}

//プレーヤーのスコーアをゲットする
//==================================================
int SceneManager::GetEndScore(void) {
	return NewScore;
}

//今まで最高のスコーアを取る
//==================================================
int SceneManager::GetEndScoreBest(void) {
	return OldScore;
}