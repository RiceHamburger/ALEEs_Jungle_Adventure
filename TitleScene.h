//==================================================
//  タイトル画面のクラス [TitleScene.h]        Autor:ロ
//==================================================
#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "BaseScene.h"
#include "sprite.h"

class TitleScene :public BaseScene {
public:
	TitleScene();
	~TitleScene();
	void Update();
	void Draw();
	void LostDevice();
	void ResetDevice();

private:
	const int TITLE_TIME = 500;
	const int TITLETEXT_ALPHA = 255;
	int countTime = TITLE_TIME;
	int btn_alpha = TITLETEXT_ALPHA;
	bool startFadeInOut = false;

	Sprite *m_UI;
};

#endif // TITLESCENE_H_