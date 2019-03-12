//==================================================
//  スコアクラス [Score.h]        Autor:ロ
//==================================================

#ifndef SCORE_H_
#define SCORE_H_

#define SCORE_X (130.0f)
#define SCORE_Y (22.0f)

class Score
{
public:
	static void Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero);
	static void Score_Init();
	static void Score_Uninit();
private:

};


#endif // SCORE_H_