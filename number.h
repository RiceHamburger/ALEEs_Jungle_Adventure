#ifndef NUMBER_H_
#define NUMBER_H_

#define NUMBER_WIDTH	(32)
#define NUMBER_HEIGHT	(32)

// 0 <= n <= 9
void Number_Draw(float x, float y, int n);
void Number_Init();
void Number_Uninit();

#endif // NUMBER_H_