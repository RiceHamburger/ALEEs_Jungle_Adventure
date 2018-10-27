//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// OP
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BOSS
	SOUND_LABEL_BGM003,			// END
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_ENEMYSHOT,	// �G�l�~�[�e���ˉ�
	SOUND_LABEL_SE_HIT,			// �v���[���[�q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_ENEMYHITED,	// �G�l�~�[�q�b�g���ꂽ
	SOUND_LABEL_SE_BOSSHITED,	// BOSS�q�b�g���ꂽ
	SOUND_LABEL_SE_PLAYERHITED,	// PLAYER�q�b�g���ꂽ
	SOUND_LABEL_SE_KEYDOWN,		// GAME START
	SOUND_LABEL_SE_PLAYERDIE,	// �v���[���[DIE
	SOUND_LABEL_SE_BOSSSHOT,	// BOSS�e���ˉ�
	SOUND_LABEL_SE_BOSSDIE,		// BOSS DIE
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
