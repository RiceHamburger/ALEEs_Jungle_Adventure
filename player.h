#ifndef PLAYER_H_
#define PLAYER_H_
#include <d3dx9.h>
#include "texture.h"
#include "object.h"

#define PLAYER_ANIMATION_TIME (4)
#define PLAYER_INVINCIBLE_TIME (20)
/*#define MAP_NUM_X (42)
#define MAP_NUM_Y (16)*/

#define MAP_NUM_X (84)
#define MAP_NUM_Y (32)

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

	int* WalkRank;
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
};


#endif // PLAYER_H_