//==================================================
//  �V�[���̃}�l�[�W���[�N���X [SceneManager.h]        Autor:��
//==================================================
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include "BaseScene.h"

class SceneManager {
public:
	enum GameStatus
	{
		TITLE,      // �Q�[���̃^�C�g��
		LOSE,		// FADE IN
		GAME,		// �Q�[���̐i�s
		RESULT		// �Q�[���I�[�o�[
	};
	static void ChangeScene(GameStatus scene);  //�V�[���������ɂ���ĕς���֐�
	static void Update();						//���݂̃V�[���̍X�V�֐�
	static void Draw();							//���݂̃V�[���̕`��֐�

	static void LostDevice();					//�O��̃f�o�C�X����
	static void ResetDevice();					//�f�o�C�X�����Z�b�g����

	//this project only
	static void SetEndScore(int s);				//�v���[���[�̃X�R�[�A��ݒ肷��
	static int GetEndScore(void);				//�v���[���[�̃X�R�[�A���Q�b�g����
	static int GetEndScoreBest(void);			//���܂ōō��̃X�R�[�A�����
private:
	static BaseScene* m_pScene;					//���݂̃V�[��

	//this project only
	static int NewScore;						//���������X�R�[�A
	static int OldScore;						//�O��ō��̃X�R�[�A
};

#endif // SCENEMANAGER_H_