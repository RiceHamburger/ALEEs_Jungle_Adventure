//==================================================
//  ゲーム画面のクラス [GameScene.h]        Autor:ロ
//==================================================
#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "BaseScene.h"
#include "sprite.h"
#include "Camera.h"
#include "player.h"
#include "boss.h"
#include "background.h"
#include <string>

class GameScene :public BaseScene {
public:
	//魔王戦が始まったら移動できる範囲を出来なくなる用の配列インデックス
	static const int MAP_CLOSE_Y = 10;
	static const int MAP_CLOSE_X_MAX = 76;
	static const int MAP_CLOSE_X_MIN = 70;

	//コンストラクタ
	GameScene();
	//デストラクタ
	~GameScene();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// 終了処理
	void Uninit();
	//前回のデバイス処理
	void LostDevice();
	//デバイスをリセット処理
	void ResetDevice();
	//ゲーム終了処理
	static void LevelClear(void);
	//カメラのフォローをキャンセルする
	static void CameraCancelFollow(void);

	//プレーヤーのポインタを取る
	static Player* GetPlayer(void);
	//魔王のポインタを取る
	static Boss* GetBoss(void);
	//マップ配列のポインタを取る
	static int* GetCanWalkRange(void);

	//画面の範囲内に攻撃する
	void EnemyCanAttackCheck(void);

	//マップを読み込み
	void loadMAP(int m, int n);

private:
	//地図の移動範囲
	static int CanWalkRange[MAP_NUM_Y][MAP_NUM_X];
	//魔王の移動ターゲット
	static Vector2D boss_target[BOSS_TARGET];

	//カメラポインタ変数
	static Camera *camera;
	//背景ポインタ変数
	BackGround *p_background;
	//背景の木のポインタ変数
	BackGround *p_background_tree;
	//プレーヤー変数
	static Player player;
	//魔王変数
	static Boss p_boss;

	//Boss
	//カメラは移動したかの判定用BOOL変数
	static bool CameraMove;
	//魔王のエリアに入るの判定範囲BOOL変数
	static bool BossShowArea_on;
	//フェイトイン/アウトBOOL変数
	static bool startFadeInOut;
	//ゲーム終了の判定BOOL変数
	static bool gameOver;
};

#endif // GAMESCENE_H_