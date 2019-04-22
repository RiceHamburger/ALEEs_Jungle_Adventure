//==================================================
//  タイトル画面のクラス [TitleScene.h]        Autor:ロ
//==================================================
#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "BaseScene.h"
#include "sprite.h"

// タイトル画面クラス
class TitleScene :public BaseScene {
public:
	TitleScene();						//コンストラクタ
	~TitleScene();						//デストラクタ
	void Update();						//更新処理
	void Draw();						//描画処理
	void LostDevice();
	void ResetDevice();

private:
	const int TITLE_TIME = 500;			//定数定義、0.5秒内にフレッシュする
	const int TITLETEXT_ALPHA = 255;	//定数定義、フレッシュ用のアルファ最大値
	int countTime = TITLE_TIME;			//計算用カウント
	int btn_alpha = TITLETEXT_ALPHA;	//提示文字のアルファ値
	bool startFadeInOut = false;		//キーを二回で入力しないように設定したスウィッチ

	Sprite *m_UI;						//画面の描画オブジェクト
};

#endif // TITLESCENE_H_