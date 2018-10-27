#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
#include "player.h"
#include "boss.h"

//close door
/*#define MAP_CLOSE_Y (5)
#define MAP_CLOSE_X_MAX (37)
#define MAP_CLOSE_X_MIN (35)*/
#define MAP_CLOSE_Y (10)
#define MAP_CLOSE_X_MAX (76)
#define MAP_CLOSE_X_MIN (70)

void Level_one_Init(void);
void Level_one_Update(void);
void Level_one_Draw(void);
void Level_one_Uninit(void);

void LevelClear(void);
void CameraCancelFollow(void);

Player* GetPlayer(void);
Boss* GetBoss(void);

//check suraimu can be camera to see
void EnemyCanAttackCheck(void);

#endif