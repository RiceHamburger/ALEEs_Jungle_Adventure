//==================================================
//  �V�[���̊�b�N���X [BaseScene.h]        Autor:��
//==================================================
#ifndef BASESCENE_H_
#define BASESCENE_H_

#include "D3Dsetup.h"

//�V�[���̊�b�N���X
class BaseScene {
public:
	//virtual void Init() = 0;
	virtual void Update() = 0;		//���ۓI�ȍX�V�����֐�
	virtual void Draw() = 0;		//���ۓI�ȕ`�揈���֐�
	virtual void LostDevice() = 0;	//���ۓI�ȍŌ�̃f�o�C�X�����֐�
	virtual void ResetDevice() = 0;	//���ۓI�ȃ��Z�b�g�̃f�o�C�X�����֐�
};

#endif // BASESCENE_H_