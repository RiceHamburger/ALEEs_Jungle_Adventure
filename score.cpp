//==================================================
//  スコアクラス [Score.cpp]        Autor:ロ
//==================================================
#include "Number.h"
#include "Score.h"

//描画処理
//==================================================
void Score::Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero)
{
	// カンスト用の最大数値を作る
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++) {
		count_stop_score *= 10;
	}

	if (score >= count_stop_score) {
		score = count_stop_score - 1;
	}


	if (bZero) {
		for (int i = 0; i < fig; i++) {
			int n = score % 10;
			score /= 10;

			Number::Number_Draw(x + NUMBER_WIDTH * (fig - (i + 1)), y, n);
		}
	}
}

// 初期化処理
//==================================================
void Score::Score_Init() {
	Number::Number_Init();
}

//終了処理
//==================================================
void Score::Score_Uninit() {
	Number::Number_Uninit();
}