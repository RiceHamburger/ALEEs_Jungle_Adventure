//==================================================
//  �^�C�g����ʂ̃N���X [TitleScene.h]        Autor:��
//==================================================
#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "BaseScene.h"
#include "sprite.h"

// �^�C�g����ʃN���X
class TitleScene :public BaseScene {
public:
	TitleScene();						//�R���X�g���N�^
	~TitleScene();						//�f�X�g���N�^
	void Update();						//�X�V����
	void Draw();						//�`�揈��
	void LostDevice();
	void ResetDevice();

private:
	const int TITLE_TIME = 500;			//�萔��`�A0.5�b���Ƀt���b�V������
	const int TITLETEXT_ALPHA = 255;	//�萔��`�A�t���b�V���p�̃A���t�@�ő�l
	int countTime = TITLE_TIME;			//�v�Z�p�J�E���g
	int btn_alpha = TITLETEXT_ALPHA;	//�񎦕����̃A���t�@�l
	bool startFadeInOut = false;		//�L�[����œ��͂��Ȃ��悤�ɐݒ肵���X�E�B�b�`

	Sprite *m_UI;						//��ʂ̕`��I�u�W�F�N�g
};

#endif // TITLESCENE_H_