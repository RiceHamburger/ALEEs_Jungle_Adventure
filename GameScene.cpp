//==================================================
//  ゲーム画面のクラス [GameScene.cpp]        Autor:ロ
//==================================================
#include <time.h>
#include <fstream>
#include <sstream>
#include "GameScene.h"
#include "D3DInput.h"
#include "texture.h"
#include "SceneManager.h"
#include "EnemyManager.h"
#include "bulletManager.h"
#include "ExplosionManager.h"
#include "TonicManager.h"
#include "WaterManager.h"
#include "Score.h"
#include "sound.h"
#include "healthBar.h"
#include "PlayerUI.h"
#include "ItemUI.h"
#include "fade.h"
#include "Judgment.h"
using namespace std;

// 静的メンバ変数
//==================================================
//マップ範囲
int	GameScene::CanWalkRange[MAP_NUM_Y][MAP_NUM_X];
//フェイトインアウト用チェック
bool GameScene::startFadeInOut = false;
//ゲーム実行チェック
bool GameScene::gameOver = false;
//bossの移動座標
Vector2D GameScene::boss_target[BOSS_TARGET] = {
	{ 2189,823 },{ 2189,741 },{ 1968,823 },{ 2410,823 }
};
//プレーヤーオブジェクト宣言
Player GameScene::player;
//カメラオブジェクト宣言
Camera *GameScene::camera;
//bossオブジェクト宣言
Boss GameScene::p_boss;
//カメラ移動チェック
bool GameScene::CameraMove;
//boss実行開始範囲チェック
bool GameScene::BossShowArea_on;

//インスタンス
//==================================================
GameScene::GameScene() {
	srand((unsigned)time(NULL));

	//フェイトイン設定する
	startFadeInOut = true;
	//ゲーム終了の判定
	gameOver = false;
	//カメラは移動したかの判定、初期値はFALSE
	CameraMove = false;
	//魔王のエリアに入るの判定範囲
	BossShowArea_on = true;

	//マップを読み込み
	loadMAP(32, 84);

	//CAMERA初期化
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, 0, DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
	//プレーヤーをフォローする
	camera->Follow(&player);

	//player初期化
	//座標
	Vector2D pos = { 0.0f, 30.0f };
	//初期速度
	D3DXVECTOR2 g_PlayerSpeed(0.0f, 0.0f);
	//座標、状態、速度、画像、テクスチャのX数量、テクスチャのY数量
	player.InitPlayer(pos, PlayerState_Front, g_PlayerSpeed, kMAJYO, 4, 4);
	//スプライト初期化
	player.InitSprite();
	//スコーア初期設定する
	player.SetScore(0);
	//HPの初期設定する
	player.SetLife(HEALTHBAR_TOTAL);
	//プレーヤー移動できる範囲配列を設定する
	player.SetWalkRang(&CanWalkRange[0][0]);

	//boss
	p_boss.Init({ 2189.0f, 1160.0f }, BOSS_IMG, 2, 0);
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
	EnemyManager::Enemy_Manager_Init();

	BulletManager::Bullet_Manager_Init();

	ExplosionManager::Explosion_Manager_Init();

	TonicManager::Tonic_Manager_Init();

	//water
	WaterManager::Water_Manager_Init();

	//UI
	Score::Score_Init();

	Healthbar::Healthbar_Init();
	PlayerUI::playerUI_Init();
	ItemUI::itemUI_Init();

	//fadeout
	g_Fade->Fade_Start(false, 500, D3DCOLOR_RGBA(0, 0, 0, 0));

	for (int i = MAP_CLOSE_X_MIN;i <= MAP_CLOSE_X_MAX;i++) {
		CanWalkRange[MAP_CLOSE_Y][i] = 0;
	}
}

//デストラクタ
//==================================================
GameScene::~GameScene() {
	Uninit();
}

//更新処理
//==================================================
void GameScene::Update() {

	if (g_Fade->Fade_IsFade()) {
		return;
	}
	else if (!g_Fade->Fade_IsFade() && startFadeInOut) {
		PlaySound(SOUND_LABEL_BGM001);
		startFadeInOut = false;
	}

	if (BossShowArea_on) {
		Judgment::StartShowBoss();
	}

	//CameraMove to final point
	if (CameraMove) {
		float w = CAMERA_TARGET_X - camera->GetcameraX();
		float h = CAMERA_TARGET_Y - camera->GetcameraY();
		float radian = atan2f(h, w);
		camera->SetPositionX(cosf(radian) * 2);
		camera->SetPositionY(sinf(radian) * 2);
		if ((CAMERA_TARGET_X - camera->GetcameraX())*(CAMERA_TARGET_X - camera->GetcameraX()) + (CAMERA_TARGET_Y - camera->GetcameraY())*(CAMERA_TARGET_Y - camera->GetcameraY()) <= 10) {
			CameraMove = false;

			StopSound(SOUND_LABEL_BGM001);

			PlaySound(SOUND_LABEL_BGM002);

			for (int i = MAP_CLOSE_X_MIN;i <= MAP_CLOSE_X_MAX;i++) {
				CanWalkRange[MAP_CLOSE_Y][i] = 1;
			}

			//close enemy live
			EnemyManager::SetAllEnemyLive(false);

			p_boss.SetActiveflag(true);
		}
	}

	if (gameOver && !g_Fade->Fade_IsFade()) {
		StopSound(SOUND_LABEL_BGM002);
		SceneManager::ChangeScene(SceneManager::RESULT);
		return;
	}

	if (!CameraMove) {
		player.Update();
		player.PlayerControl();
	}

	BulletManager::Bullet_Manager_Update();

	Judgment::Judgment_Bullet_vs_Enemy();
	Judgment::Judgment_Player_vs_Enemy();
	Judgment::Judgment_Bullet_vs_Player();

	//item
	Judgment::Judgment_Tonic_vs_Player();
	//red enemy
	Judgment::Judgment_Bullet_vs_EnemyRed();
	Judgment::Judgment_Player_vs_EnemyRed();
	Judgment::Judgment_Player_vs_EnemyRedRange();

	Judgment::Judgment_Bullet_vs_Boss();
	Judgment::Judgment_Player_vs_Boss();
	Judgment::Judgment_BigBullet_vs_Player();

	ExplosionManager::Explosion_Manager_Update();

	//enemy auto attack
	EnemyCanAttackCheck();

	//water
	WaterManager::Water_Manager_Update();

	//show boss if boss alife
	if (p_boss.GetActiveflag() && p_boss.GetLiveFlag()) {
		p_boss.Active();
	}
	else {
		EnemyManager::Enemy_Manager_Update();
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

//描画処理
//==================================================
void GameScene::Draw() {
	//CAMERA
	if (camera)
	{
		camera->SetTransform();
	}

	//bg
	p_background->DrawSprite();
	//water
	WaterManager::Water_Manager_Draw();

	//enemy
	EnemyManager::Enemy_Manager_Draw();
	//bullet
	BulletManager::Bullet_Manager_Draw();
	//player
	player.DrawSprite(player.GetRect());

	//boss
	if (p_boss.GetActiveflag()) {
		p_boss.DrawSprite(p_boss.GetRect());
	}

	//explosion
	ExplosionManager::Explosion_Manager_Draw();

	//tonic
	TonicManager::Tonic_Manager_Draw();

	p_background_tree->DrawSprite();

	//UI
	Score::Score_Draw(camera->GetcameraLX() + SCORE_X, camera->GetcameraLY() + SCORE_Y, player.GetScore(), 5, NULL, true);
	PlayerUI::playerUI_Draw(camera->GetcameraLX() + PLAYERUI_X, camera->GetcameraLY() + PLAYERUI_Y);
	Healthbar::Healthbar_Draw(camera->GetcameraLX() + HEALTHBAR_X, camera->GetcameraLY() + HEALTHBAR_Y, player.GetLife());

	//item
	if (player.GetItemCheck()) {
		ItemUI::itemUI_Draw(camera->GetcameraLX() + ITEMUI_X, camera->GetcameraLY() + ITEMUI_Y);
	}

	if (p_boss.GetActiveflag()) {
		p_boss.DrawBloodSprite(camera->GetcameraLX(), camera->GetcameraLY() + BOSS_HEALTHBARUI_Y, camera->GetcameraLX() + BOSS_HEALTHBAR_X, camera->GetcameraLY() + BOSS_HEALTHBAR_Y);
	}
}

//終了処理
//==================================================
void GameScene::Uninit() {
	BulletManager::Bullet_Manager_Uninit();
	ExplosionManager::Explosion_Manager_Uninit();
	EnemyManager::Enemy_Manager_Uninit();
	TonicManager::Tonic_Manager_Uninit();

	//water
	WaterManager::Water_Manager_Uninit();

	//UI
	Score::Score_Uninit();
	PlayerUI::playerUI_Uninit();
	Healthbar::Healthbar_Uninit();
	p_boss.BloodSprite_Uninit();
	ItemUI::itemUI_Uninit();

	//boss
	p_boss.Sprite_Uninit();
	p_boss.DeletTargetArr();

	//CAMERA
	if (camera) { delete camera; camera = NULL; }
	if (p_background) { delete p_background; p_background = NULL; }
	if (p_background_tree) { delete p_background_tree; p_background_tree = NULL; }
}

//前回デバイス処理
//==================================================
void GameScene::LostDevice() {
	
}

//デバイスをリセット処理
//==================================================
void GameScene::ResetDevice() {
	
}

//プレーヤーポインタを取る
//==================================================
Player* GameScene::GetPlayer(void) {
	return &player;
}

//BOSSポインタを取る
//==================================================
Boss* GameScene::GetBoss(void) {
	return &p_boss;
}

//ゲーム終了
//==================================================
void GameScene::LevelClear(void) {
	//save now score
	SceneManager::SetEndScore(player.GetScore());

	g_Fade->Fade_Start(true, 500, D3DCOLOR_RGBA(0, 0, 0, 255));
	gameOver = true;
}

//カメラフォローを消す
//==================================================
void GameScene::CameraCancelFollow(void) {
	camera->Unfollow();
	CameraMove = true;
	BossShowArea_on = false;
}

//エネミーが攻撃できるか
//==================================================
void GameScene::EnemyCanAttackCheck(void) {
	//if enemy in camera range
	Enemy *Enemys = EnemyManager::EnemyMgrGetEnemy();
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

//マップ配列を取る
//==================================================
int* GameScene::GetCanWalkRange(void) {
	return &CanWalkRange[0][0];
}

//マップを読み込み
void GameScene::loadMAP(int m, int n) {
	//ファイルを読み込み用変数を宣言
	std::ifstream mapFile;
	std::string line;
	
	//ファイルを開く
	mapFile.open("map.txt", std::ios_base::in);

	//順番でマップ配列に入る
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			//カンマで数値を分ける
			getline(mapFile, line, ',');
			std::istringstream iss(line);
			//文字から数値に変わって入る
			CanWalkRange[i][j] = std::stoi(line);
		}
	}
	//ファイルを閉める
	mapFile.close();
}