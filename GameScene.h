//==================================================
//  ÉQÅ[ÉÄâÊñ ÇÃÉNÉâÉX [GameScene.h]        Autor:Éç
//==================================================
#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "BaseScene.h"
#include "sprite.h"
#include "Camera.h"
#include "player.h"
#include "boss.h"
#include "background.h"

class GameScene :public BaseScene {
public:
	static const int MAP_CLOSE_Y = 10;
	static const int MAP_CLOSE_X_MAX = 76;
	static const int MAP_CLOSE_X_MIN = 70;

	GameScene();
	~GameScene();
	void Update();
	void Draw();
	void Uninit();
	void LostDevice();
	void ResetDevice();

	static void LevelClear(void);
	static void CameraCancelFollow(void);

	static Player* GetPlayer(void);
	static Boss* GetBoss(void);
	static int* GetCanWalkRange(void);

	//âÊñ ÇÃîÕàÕì‡Ç…çUåÇÇ∑ÇÈ
	void EnemyCanAttackCheck(void);

private:
	//ínê}
	static int CanWalkRange[MAP_NUM_Y][MAP_NUM_X];
	static Vector2D boss_target[BOSS_TARGET];

	static Camera *camera;
	BackGround *p_background;
	BackGround *p_background_tree;
	static Player player;
	static Boss p_boss;

	//Boss
	static bool CameraMove;
	static bool BossShowArea_on;

	static bool startFadeInOut;
	static bool gameOver;
};

#endif // GAMESCENE_H_