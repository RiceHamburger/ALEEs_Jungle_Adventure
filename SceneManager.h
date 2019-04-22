//==================================================
//  シーンのマネージャークラス [SceneManager.h]        Autor:ロ
//==================================================
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "BaseScene.h"

class SceneManager {
public:
	enum GameStatus
	{
		TITLE,      // ゲームのタイトル
		LOSE,		// FADE IN
		GAME,		// ゲームの進行
		RESULT		// ゲームオーバー
	};
	static void ChangeScene(GameStatus scene);  //シーンを引数によって変える関数
	static void Update();						//現在のシーンの更新関数
	static void Draw();							//現在のシーンの描画関数

	static void LostDevice();					//前回のデバイス処理
	static void ResetDevice();					//デバイスをリセット処理

	//this project only
	static void SetEndScore(int s);				//プレーヤーのスコーアを設定する
	static int GetEndScore(void);				//プレーヤーのスコーアをゲットする
	static int GetEndScoreBest(void);			//今まで最高のスコーアを取る
private:
	static BaseScene* m_pScene;					//現在のシーン

	//this project only
	static int NewScore;						//今回取ったスコーア
	static int OldScore;						//前回最高のスコーア
};

#endif // SCENEMANAGER_H_