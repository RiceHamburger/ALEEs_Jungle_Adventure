#ifndef COMMON_H_
#define COMMON_H_

typedef struct{
	float x;
	float y;
}Vector2D;

typedef struct{
	float cx, cy;
	float r;
}Circle;

//画面サイト
//#define SCREEN_WIDTH (1024)
//#define SCREEN_HEIGHT (568)
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (768)

#endif // COMMON_H_

//ヘッダファイルのお約束

//ヘッダファイルに書いて良いもの

//定数
//関数のプロトタイプ宣言
//構造体の宣言
//enum
//typedef
//inline関数　マクロ
//exturn.goto 使えるように