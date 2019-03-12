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

	static void LostDevice();					
	static void ResetDevice();			

	//this project only
	static void SetEndScore(int s);
	static int GetEndScore(void);
	static int GetEndScoreBest(void);
private:
	static BaseScene* m_pScene;					//���݂̃V�[��

	//this project only
	static int NewScore;
	static int OldScore;
};

#endif // SCENEMANAGER_H_