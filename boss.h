#ifndef BOSS_H_
#define BOSS_H_
#include "texture.h"
#include "object.h"

//–‚‰¤‰æ‘œ‚ÌL‚³
#define BOSS_WIDTH (228)
#define BOSS_HEIGHT (449)
#define BOSS_SCORE (2)
#define BOSS_SPEED_MAX (1.0f)
#define BOSS_SPEED_MIN (0.4f)
#define BOSS_ANIMATION_TIME (60)

#define BOSS_BODYDAMAGE (30)

//blood
#define BOSS_HEALTHBAR_WIDTH	(700)
#define BOSS_HEALTHBAR_HEIGHT (20)
#define BOSS_HEALTHBAR_TOTAL	(30)
#define BOSS_HEALTHBAR_X (160)
#define BOSS_HEALTHBAR_Y (717)
#define BOSS_HEALTHBARUI_Y (690)

//–‚‰¤‚Ì•’ÊUŒ‚‚ÌŠÔŠÔŠu
#define BOSS_ATTACK_TIME (600)
//–‚‰¤‚Ì‘å‚«‚¢UŒ‚‚ÌŠÔŠÔŠuMAX
#define BOSS_BIGATTACK_TIME_MAX (1200)
//–‚‰¤‚Ì‘å‚«‚¢UŒ‚‚ÌŠÔŠÔŠuMIN
#define BOSS_BIGATTACK_TIME_MIN (300)

//effect time
#define BOSS_EFFECT_TIME (100)

//–‚‰¤À•W‚Ì‰Šú’l
#define BOSS_Y (145)
//–‚‰¤‚ÌˆÚ“®ƒ^[ƒQƒbƒg”—Ê
#define BOSS_TARGET (4)

typedef enum
{
	BossState_Show,
	BossState_Move,
	BossState_Die
}BossState;

class Boss :public Object {
private:
	int life;
	int score;
	float speed;
	int bodydamage;
	bool bossActiv;
	BossState state;

	RECT text_rec;
	int textureX;
	int textureY;
	int textureX_index;
	int textureY_index;
	int textureX_NUM;
	int textureY_NUM;
	int aniTime;

	//blood
	LPD3DXSPRITE health_sprite;
	LPD3DXSPRITE healthUI_sprite;
	D3DXVECTOR3 health_Position;
	D3DXVECTOR3 healthUI_Position;
	RECT health_rec;
	float health_percent;
	float oldHealth;

	//attack time
	int attackTime;
	int BigattackTime;

	//be attack effect
	bool Effect;
	int Effect_time;

	Vector2D targetArr[BOSS_TARGET];
	int targetIndex;
	int activeCount;

public:
	void Init(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY);
	void Active();
	void SetLife(int Life);
	void SetScore(int Score);
	void SetSpeed(float Speed);
	int GetScore();
	int GetLife();
	RECT *GetRect();
	void DeletTargetArr();
	void SetTargetArr(Vector2D MtargetArr);
	void SetTargetIndex(int index);

	//blood
	void InitBloodSprite();
	void BloodSprite_Uninit();
	void DrawBloodSprite(float UIx, float UIy, float BARx, float BARy);

	void SetActiveflag(bool flag);
	bool GetActiveflag();

	int GetEnemyBodyDamage();

	float getRadian(float X1, float Y1, float X2, float Y2);

	//auto attack
	void Attack();

	//effect
	void SetDamageEffect(bool sw);
};

#endif //BOSS_H_