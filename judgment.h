//==================================================
//  裁きのクラス [Judgment.h]        Autor:ロ
//==================================================
#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_

#include "common.h"
#include "D3Dsetup.h"

class Judgment
{
public:
	static bool Collision_HitCircle(const Circle* circle_a, const Circle* circle_b);
	//ポインタのコピー、四bit以上

	static void Judgment_Bullet_vs_Enemy(void);

	//red
	static void Judgment_Bullet_vs_EnemyRed(void);
	static void Judgment_Player_vs_EnemyRed(void);
	static void Judgment_Player_vs_EnemyRedRange(void);

	static void Judgment_Bullet_vs_Player(void);
	static void Judgment_Player_vs_Enemy(void);

	//item
	static void Judgment_Tonic_vs_Player(void);

	//boss
	static void Judgment_Bullet_vs_Boss(void);
	static void Judgment_Player_vs_Boss(void);
	static void Judgment_BigBullet_vs_Player(void);

	//final collision area
	static void StartShowBoss(void);
private:
	static RECT endArea;
};

#endif //JUDGEMENT_H_