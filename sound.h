//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// OP
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BOSS
	SOUND_LABEL_BGM003,			// END
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SE_ENEMYSHOT,	// エネミー弾発射音
	SOUND_LABEL_SE_HIT,			// プレーヤーヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_ENEMYHITED,	// エネミーヒットされた
	SOUND_LABEL_SE_BOSSHITED,	// BOSSヒットされた
	SOUND_LABEL_SE_PLAYERHITED,	// PLAYERヒットされた
	SOUND_LABEL_SE_KEYDOWN,		// GAME START
	SOUND_LABEL_SE_PLAYERDIE,	// プレーヤーDIE
	SOUND_LABEL_SE_BOSSSHOT,	// BOSS弾発射音
	SOUND_LABEL_SE_BOSSDIE,		// BOSS DIE
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
