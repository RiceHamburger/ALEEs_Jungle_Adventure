#ifndef SCORE_H_
#define SCORE_H_

#define SCORE_X (130.0f)
#define SCORE_Y (22.0f)

void Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero);
void Score_Init();
void Score_Uninit();

#endif // SCORE_H_