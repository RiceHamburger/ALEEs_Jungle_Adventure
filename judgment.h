#ifndef JUDGEMENT_H_
#define JUDGEMENT_H_

#include "common.h"
#include "direct3d_setup.h"

bool Collision_HitCircle(const Circle* circle_a, const Circle* circle_b);
//ポインタのコピー、四bit以上

void Judgment_Bullet_vs_Enemy(void);
void Judgment_Bullet_vs_Player(void);
bool Judgment_Player_vs_Tree(D3DXVECTOR2 vec);
void Judgment_Player_vs_Enemy(void);

//boss
void Judgment_Bullet_vs_Boss(void);
void Judgment_Player_vs_Boss(void);
void Judgment_BigBullet_vs_Player(void);

//final collision area
void StartShowBoss(void);

#endif //JUDGEMENT_H_