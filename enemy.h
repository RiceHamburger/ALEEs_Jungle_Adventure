#ifndef ENEMY_H_
#define ENEMY_H_
#include "texture.h"
#include "object.h"

#define ENEMY_MAX (6)
#define ENEMY_SPEED_MAX (2)
#define ENEMY_SPEED_MIN (1)
#define ENEMY_WIDTH (42)
#define ENEMY_HEIGHT (32)
#define ENEMY_SCORE (1)
#define ENEMY_ANIMATION_TIME (6)

#define ENEMY_TARGET (4)
#define ENEMY_BODYDAMAGE (20)

//blood
#define ENEMY_HEALTHBAR_WIDTH	(32)
#define ENEMY_HEALTHBAR_HEIGHT (4)
#define ENEMY_HEALTHBAR_TOTAL	(5)

//respawn
#define ENEMY_RETIME (300)

//attack time
#define ENEMY_ATTACK_TIME (60)

//effect time
#define ENEMY_EFFECT_TIME (20)

class Enemy :public Object {
private:
	int life;
	int score;
	float speed;
	int bodydamage;

	RECT text_rec;
	int textureX;
	int textureY;
	int textureX_index;
	int textureY_index;
	int textureX_NUM;
	int textureY_NUM;
	int aniTime;

	int targetIndex;

	Vector2D targetArr[ENEMY_TARGET];

	//blood
	LPD3DXSPRITE health_sprite;
	RECT health_rec;
	float health_percent;

	int reSpawnTime;

	//attack time
	int attackTime;

	//be attack effect
	bool Effect;
	int Effect_time;
public:
	Enemy();
	~Enemy();
	void InitEnemy(Vector2D pos, TEXTURE_NAME tex_name, int tex_pic_numX, int tex_pic_numY);
	void EnemyActive();
	void EnemyDestroy();
	void SetLife(int Life);
	void SetScore(int Score);
	void SetSpeed(float Speed);

	void EnemyRespawn();

	float GetSpeed();
	int GetScore();
	int GetLife();
	RECT *GetRect();
	void DeletTargetArr();
	void SetTargetArr(Vector2D MtargetArr);

	float getRadian(float X1, float Y1, float X2, float Y2);
	void SetTargetIndex(int index);

	int GetEnemyBodyDamage();

	//blood
	void InitBloodSprite();
	void BloodSprite_Uninit();
	void DrawBloodSprite();

	//auto attack
	void EnemyAttack();

	//effect
	void SetDamageEffect(bool sw);
};

#endif //ENEMY_H_