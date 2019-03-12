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

	static void LostDevice();					
	static void ResetDevice();			

	//this project only
	static void SetEndScore(int s);
	static int GetEndScore(void);
	static int GetEndScoreBest(void);
private:
	static BaseScene* m_pScene;					//現在のシーン

	//this project only
	static int NewScore;
	static int OldScore;
};

#endif // SCENEMANAGER_H_