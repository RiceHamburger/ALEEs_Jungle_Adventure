//==================================================
//  タイトル画面のクラス [EndScene.h]        Autor:ロ
//==================================================
#ifndef ENDSCENE_H_
#define ENDSCENE_H_

#include "BaseScene.h"
#include "sprite.h"

class EndScene :public BaseScene {
public:
	EndScene();
	~EndScene();
	void Update();
	void Draw();
	void LostDevice();
	void ResetDevice();

private:
	static bool gameToEndFadeIn;
	static bool endToStartFadeInOut;
	static bool endFadeOver;
	static int endShowScore;
	static int endShowScoreBest;
	Sprite *m_UI;
};

#endif // ENDSCENE_H_