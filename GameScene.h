//==================================================
//  �Q�[����ʂ̃N���X [GameScene.h]        Autor:��
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
	//�����킪�n�܂�����ړ��ł���͈͂��o���Ȃ��Ȃ�p�̔z��C���f�b�N�X
	static const int MAP_CLOSE_Y = 10;
	static const int MAP_CLOSE_X_MAX = 76;
	static const int MAP_CLOSE_X_MIN = 70;

	//�R���X�g���N�^
	GameScene();
	//�f�X�g���N�^
	~GameScene();
	// �X�V����
	void Update();
	// �`�揈��
	void Draw();
	// �I������
	void Uninit();
	//�O��̃f�o�C�X����
	void LostDevice();
	//�f�o�C�X�����Z�b�g����
	void ResetDevice();
	//�Q�[���I������
	static void LevelClear(void);
	//�J�����̃t�H���[���L�����Z������
	static void CameraCancelFollow(void);

	//�v���[���[�̃|�C���^�����
	static Player* GetPlayer(void);
	//�����̃|�C���^�����
	static Boss* GetBoss(void);
	//�}�b�v�z��̃|�C���^�����
	static int* GetCanWalkRange(void);

	//��ʂ͈͓̔��ɍU������
	void EnemyCanAttackCheck(void);

	//�}�b�v��ǂݍ���
	void loadMAP(int m, int n);

private:
	//�n�}�̈ړ��͈�
	static int CanWalkRange[MAP_NUM_Y][MAP_NUM_X];
	//�����̈ړ��^�[�Q�b�g
	static Vector2D boss_target[BOSS_TARGET];

	//�J�����|�C���^�ϐ�
	static Camera *camera;
	//�w�i�|�C���^�ϐ�
	BackGround *p_background;
	//�w�i�̖؂̃|�C���^�ϐ�
	BackGround *p_background_tree;
	//�v���[���[�ϐ�
	static Player player;
	//�����ϐ�
	static Boss p_boss;

	//Boss
	//�J�����͈ړ��������̔���pBOOL�ϐ�
	static bool CameraMove;
	//�����̃G���A�ɓ���̔���͈�BOOL�ϐ�
	static bool BossShowArea_on;
	//�t�F�C�g�C��/�A�E�gBOOL�ϐ�
	static bool startFadeInOut;
	//�Q�[���I���̔���BOOL�ϐ�
	static bool gameOver;
};

#endif // GAMESCENE_H_