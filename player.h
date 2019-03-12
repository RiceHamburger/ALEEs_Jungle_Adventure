#ifndef PLAYER_H_
#define PLAYER_H_
#include <d3dx9.h>
#include "texture.h"
#include "object.h"

#define PLAYER_ANIMATION_TIME (40)
#define PLAYER_INVINCIBLE_TIME (20)

#define MAP_NUM_X (84)
#define MAP_NUM_Y (32)

//時間
#define SHOOTE_TIME (30)
#define HIGHT_SHOOTE_TIME (600)

typedef enum
{
	PlayerState_Front,
	PlayerState_Left,
	PlayerState_Back,
	PlayerState_Right,
	PlayerState_Hit,
	PlayerState_Invincible
}PlayerState;

class Player:public Object {
private:
	int life;
	int score;
	PlayerState state;
	D3DXVECTOR2 g_PlayerSpeed;

	bool isMove;
	RECT text_rec;
	int textureX;
	int textureY;
	int textureX_index;
	int textureY_index;
	int textureX_NUM;
	int textureY_NUM;
	int aniTime;

	bool invincible;
	int invincible_time;

	//移動出来る範囲
	int* WalkRank;
	//弾を留める時間
	int canShootTime;
	//出した弾の数量
	int ShootedNum;
	//連続できない時の時間用switch
	bool renzokuShoot;
	//連続出来るかどうか
	bool canHighShoot;
	//連続SHOOT時間
	int HighShootTime;
	//プレイヤーがITEMを持っている時
	bool haveItem;

public:
	Player();
	~Player();
	void PlayerControl();
	void InitPlayer(Vector2D pos,PlayerState state, D3DXVECTOR2 g_PlayerSpeed, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY);
	void SetLife(int life);
	void SetScore(int score);
	void SetState(PlayerState state);
	int GetScore();
	int GetLife();

	void AddScore(int addscore);
	void PlayerAni();
	RECT *GetRect();

	void SetInvincible(bool sw);
	bool GetInvincible();

	void SetWalkRang(int* rang);
	bool RangCheck(float x,float y);

	//3回のShoot計算
	void checkContinuous(void);

	//連続Shoot出来る
	void SetHighShoot(bool sw);
	//連続Shoot計算
	void checkHightShoot(void);

	bool GetItemCheck(void);
	void SetItemCheck(bool sw);
};


#endif // PLAYER_H_