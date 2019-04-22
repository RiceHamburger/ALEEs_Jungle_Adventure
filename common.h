#ifndef COMMON_H_
#define COMMON_H_

//2Dベクトル構造体
typedef struct{
	float x;
	float y;
}Vector2D;

//円の構造体
typedef struct{
	float cx, cy;
	float r;
}Circle;

//ゲームの広さ設定
#define SCREEN_WIDTH (1024)
//ゲームの高さ設定
#define SCREEN_HEIGHT (768)

#endif // COMMON_H_