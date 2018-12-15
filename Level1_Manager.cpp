#include <time.h>
#include "Level1_Manager.h"
#include "enemy_Manager.h"
#include "bullet_Manager.h"
#include "explosion_Manager.h"
#include "tree_Manager.h"
#include "judgment.h"
#include "score.h"
#include "Camera.h"
#include "background.h"
#include "sound.h"
#include "game.h"

#include "fade.h"
#include "healthBar.h"
#include "playerUI.h"
#include "water_Manager.h"
#include "tonic_Manager.h"

//----ƒOƒ[ƒoƒ‹•Ï”----
static Player player;
Camera *camera;
BackGround *p_background;
BackGround *p_background_tree;
static Boss p_boss;

static int CanWalkRange[MAP_NUM_Y][MAP_NUM_X] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

Vector2D boss_target[BOSS_TARGET] = {
	{ 2189,823 },{ 2189,741 },{ 1968,823 },{ 2410,823 }
};

static bool startFadeInOut = false;
static bool gameOver = false;

//boss
static bool CameraMove;
static bool BossShowArea_on;

void Level_one_Init(void) {
	srand((unsigned)time(NULL));

	startFadeInOut = true;
	gameOver = false;
	CameraMove = false;
	BossShowArea_on = true;

	//CAMERA
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	camera->Follow(&player);

	//player
	Vector2D pos = { 0.0f, 30.0f };
	D3DXVECTOR2 g_PlayerSpeed(0.0f, 0.0f);
	player.InitPlayer(pos, PlayerState_Front, g_PlayerSpeed, kMAJYO,4,4);
	player.InitSprite();
	player.SetScore(0);
	player.SetLife(HEALTHBAR_TOTAL);
	player.SetWalkRang(&CanWalkRange[0][0]);

	//boss
	p_boss.Init({ 2189.0f, 1160.0f }, BOSS_IMG,2,0);
	p_boss.InitSprite();
	p_boss.SetLife(BOSS_HEALTHBAR_TOTAL);
	p_boss.SetScore(BOSS_SCORE);
	p_boss.SetSpeed(BOSS_SPEED_MAX);
	p_boss.InitBloodSprite();

	for (int i = 0;i < BOSS_TARGET;i++) {
		p_boss.SetTargetArr(boss_target[i]);
	}
	p_boss.SetTargetIndex(1);

	//bg
	p_background = new BackGround(LEVEL_BG, { -512.0f, -380.0f });
	p_background->SetTextureIndex(LEVEL_BG);
	p_background->InitSprite();

	//tree bg
	p_background_tree = new BackGround(LEVEL_TREEBG, { -512.0f, -380.0f });
	p_background_tree->SetTextureIndex(LEVEL_TREEBG);
	p_background_tree->InitSprite();

	//enemy
	Enemy_Manager_Init();

	Bullet_Manager_Init();

	Explosion_Manager_Init();

	Tonic_Manager_Init();

	//tree
	//Tree_Init();

	//water
	Water_Manager_Init();

	//UI
	Score_Init();

	Healthbar_Init();
	playerUI_Init();

	//fadeout
	Fade_Start(false, 30, D3DCOLOR_RGBA(0, 0, 0, 0));

	for (int i = MAP_CLOSE_X_MIN;i <= MAP_CLOSE_X_MAX;i++) {
		CanWalkRange[MAP_CLOSE_Y][i] = 0;
	}
}
void Level_one_Update(void) {

	if (Fade_IsFade()) {
		return;
	}
	else if (!Fade_IsFade() && startFadeInOut) {
		PlaySound(SOUND_LABEL_BGM001);
		startFadeInOut = false;
	}

	if (BossShowArea_on) {
		StartShowBoss();
	}

	//CameraMove to final point
	if (CameraMove) {
		float w = CAMERA_TARGET_X - camera->GetcameraX();
		float h = CAMERA_TARGET_Y - camera->GetcameraY();
		float radian = atan2f(h, w);
		camera->SetPositionX(cosf(radian)*4);
		camera->SetPositionY(sinf(radian)*4);
		if ((CAMERA_TARGET_X - camera->GetcameraX())*(CAMERA_TARGET_X - camera->GetcameraX()) + (CAMERA_TARGET_Y - camera->GetcameraY())*(CAMERA_TARGET_Y - camera->GetcameraY()) <= 10) {
			CameraMove = false;

			StopSound(SOUND_LABEL_BGM001);

			PlaySound(SOUND_LABEL_BGM002);

			for (int i = MAP_CLOSE_X_MIN;i <= MAP_CLOSE_X_MAX;i++) {
				CanWalkRange[MAP_CLOSE_Y][i] = 1;
			}
			
			//close enemy live
			SetAllEnemyLive(false);

			p_boss.SetActiveflag(true);
		}
	}

	if (gameOver && !Fade_IsFade()) {
		StopSound(SOUND_LABEL_BGM002);
		GameSceneChange(Scene_End);
		return;
	}
		
	if (!CameraMove) {
		player.Update();
		player.PlayerControl();
	}

	Bullet_Manager_Update();

	Judgment_Bullet_vs_Enemy();
	Judgment_Player_vs_Enemy();
	Judgment_Bullet_vs_Player();

	//item
	Judgment_Tonic_vs_Player();

	Judgment_Bullet_vs_Boss();
	Judgment_Player_vs_Boss();
	Judgment_BigBullet_vs_Player();

	Explosion_Manager_Update();

	//enemy auto attack
	EnemyCanAttackCheck();

	//water
	Water_Manager_Update();

	//show boss if boss alife
	if (p_boss.GetActiveflag() && p_boss.GetLiveFlag()) {
		p_boss.Active();
	}
	else {
		Enemy_Manager_Update();
	}


	//CAMERA
	if (camera)
	{
		camera->Update();
	}

	//background
	if (p_background)
	{
		p_background->Update();
	}

	//tree
	if (p_background_tree)
	{
		p_background_tree->Update();
	}
}

void Level_one_Draw(void) {

	if (camera)
	{
		camera->SetTransform();
	}

	//bg
	p_background->DrawSprite();
	//water
	Water_Manager_Draw();

	//enemy
	Enemy_Manager_Draw();
	//bullet
	Bullet_Manager_Draw();
	//player
	player.DrawSprite(player.GetRect());

	//boss
	if (p_boss.GetActiveflag()) {
		p_boss.DrawSprite(p_boss.GetRect());
	}

	//explosion
	Explosion_Manager_Draw();

	//tonic
	Tonic_Manager_Draw();

	//tree
	//Tree_Draw();
	p_background_tree->DrawSprite();

	//UI
	Score_Draw(camera->GetcameraLX() + SCORE_X, camera->GetcameraLY() + SCORE_Y, player.GetScore(), 5, NULL, true);
	playerUI_Draw(camera->GetcameraLX() + PLAYERUI_X, camera->GetcameraLY() + PLAYERUI_Y);
	Healthbar_Draw(camera->GetcameraLX() + HEALTHBAR_X, camera->GetcameraLY() + HEALTHBAR_Y, player.GetLife());

	if (p_boss.GetActiveflag()) {
		p_boss.DrawBloodSprite(camera->GetcameraLX(), camera->GetcameraLY() + BOSS_HEALTHBARUI_Y, camera->GetcameraLX() + BOSS_HEALTHBAR_X, camera->GetcameraLY() + BOSS_HEALTHBAR_Y);
	}
}

void Level_one_Uninit(void) {
	Bullet_Manager_Uninit();
	Explosion_Manager_Uninit();
	Enemy_Manager_Uninit();
	Tonic_Manager_Uninit();

	//tree
	//Tree_Uninit();

	//water
	Water_Manager_Uninit();

	//UI
	Score_Uninit();
	playerUI_Uninit();
	Healthbar_Uninit();
	p_boss.BloodSprite_Uninit();

	//boss
	p_boss.Sprite_Uninit();
	p_boss.DeletTargetArr();

	if (camera) { delete camera; camera = NULL; }
	if(p_background){ delete p_background; p_background = NULL; }
	if (p_background_tree) { delete p_background_tree; p_background_tree = NULL; }
}

Player* GetPlayer(void) {
	return &player;
}

Boss* GetBoss(void) {
	return &p_boss;
}

void LevelClear(void) {
	//save now score
	SetEndScore(player.GetScore());

	Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 255));
	gameOver = true;
}

void CameraCancelFollow(void) {
	camera->Unfollow();
	CameraMove = true;
	BossShowArea_on = false;
}

void EnemyCanAttackCheck(void) {
	//if enemy in camera range
	Enemy *Enemys = EnemyMgrGetEnemy();
	for (int j = 0;j < ENEMY_MAX;j++) {
		if (Enemys[j].GetLiveFlag()) {

			RECT enemy_rect;
			enemy_rect.left = Enemys[j].GetPosition().x;
			enemy_rect.top = Enemys[j].GetPosition().y;
			enemy_rect.right = enemy_rect.left + Enemys[j].GetWidth();
			enemy_rect.bottom = enemy_rect.top + Enemys[j].GetHeight();

			RECT dest;
			if (IntersectRect(&dest, camera->GetCameraRange(), &enemy_rect)) {
				Enemys[j].EnemyAttack();
			}
		}
	}
}